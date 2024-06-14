#include "cub3d.h"
void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

void    sky_and_floor(t_vars *vars)
{
    int y;
    int x;

    y = 0;
    while (y < SCREEN_HEIGHT / 2)
    {
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            my_mlx_pixel_put(&vars->img, x, y, vars->map_info.ceiling_color);
            x++;
        }
        y++;
    }
    // Draw floor (lower half)
    y = SCREEN_HEIGHT / 2;
    while (y < SCREEN_HEIGHT)
    {
        x = 0;
        while (x < SCREEN_WIDTH)
        {
            my_mlx_pixel_put(&vars->img, x, y, vars->map_info.floor_color);
            x++;
        }
        y++;
    }

}

void raycasting(t_vars *vars)
{
    int x; 
    int y;
    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX; //length of ray from current position to next x or y-side
    double sideDistY; //length of ray from current position to next x or y-side
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX; //what direction to step in x or y-direction (either +1 or -1)
    int stepY; //what direction to step in x or y-direction (either +1 or -1)
    int hit;
    int side;
    int lineHeight;
    int drawStart;
    int drawEnd;
    double wallX;
    int texX;
    int texY;
    unsigned int color;
    int d;
    t_img *texture;

    



    x = 0;
    while (x < SCREEN_WIDTH)
    {
        //calculate ray position and direction
        cameraX = 2 * x / (double)SCREEN_WIDTH - 1; //x-coordinate in camera space
        rayDirX = vars->dirX + vars->planeX * cameraX;
        rayDirY = vars->dirY + vars->planeY * cameraX;
        // printf("%f       %f\n",vars->dirX,vars->dirY);
        // printf("%f       %f\n",rayDirX,rayDirY);

        //which box of the map we're in
        mapX = (int)vars->posX;
        mapY = (int)vars->posY;

        //length of ray from one x or y-side to next x or y-side
        //these are derived as:
        //deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
        //deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
        //which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
        //where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
        //unlike (dirX, dirY) is not 1, however this does not matter, only the
        //ratio between deltaDistX and deltaDistY matters, due to the way the DDA
        //stepping further below works. So the values can be computed as below.
        // Division through zero is prevented, even though technical
        deltaDistX = fabs(1 / rayDirX);
        deltaDistY = fabs(1 / rayDirY);

        hit = 0; //was there a wall hit?
        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1; //what direction to step in x or y-direction (either +1 or -1)
            sideDistX = (vars->posX - mapX) * deltaDistX; //length of ray from current position to next x or y-side
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - vars->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (vars->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - vars->posY) * deltaDistY;
        }
        // printf("%d       %d\n",stepX,stepY);

        //perform DDA
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0; //was a NS or a EW wall hit?
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1; 
            }
            //Check if ray has hit a wall
            if (vars->map_info.map[mapX][mapY] > 0) 
                hit = 1;
        }
        //Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
        //hit to the camera plane. Euclidean to center camera point would give fisheye effect!
        //This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
        //for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
        //because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
        //steps, but we subtract deltaDist once because one step more into the wall was taken above.
        if (side == 0)
            perpWallDist = (mapX - vars->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - vars->posY + (1 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        
        //calculate lowest and highest pixel to fill in current stripe
        drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) 
            drawStart = 0;
        drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) 
            drawEnd = SCREEN_HEIGHT - 1;
        //load textures
        if (side == 0) 
        {
            if (rayDirX > 0) 
                texture = &vars->textures[0]; // North
            else 
                texture = &vars->textures[1]; // South
        } 
        else 
        {
            if (rayDirY > 0) 
                texture = &vars->textures[2]; // West
            else 
                texture = &vars->textures[3]; // East
        }
        
        if (side == 0) 
            wallX = vars->posY + perpWallDist * rayDirY;
        else           
            wallX = vars->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);
        
        //the x horizontal pixel of the texture will be used for the wall stripe.
        texX = (int)(wallX * (double)(texture->width));
        if (side == 0 && rayDirX > 0) 
            texX = texture->width - texX - 1;
        if (side == 1 && rayDirY < 0) 
            texX = texture->width - texX - 1;
        
        y = drawStart;
        while (y < drawEnd)
        {
            // big formula 
            // d = y * texture->height * 2 - SCREEN_HEIGHT * texture->height + lineHeight * texture->height;
            // texY = ((d * texture->height) / lineHeight) / (texture->height * 2);

            // short formula
            d = texture->height * (y * 2 - SCREEN_HEIGHT + lineHeight);
            texY = d / (lineHeight * 2);
            
            color = *(unsigned int*)(texture->addr + (texY * texture->line_length + texX * (texture->bpp / 8)));
            if (side == 1) 
                color = (color >> 1) & 8355711; // Make color darker for y-sides
            my_mlx_pixel_put(&vars->img, x, y, color);
            y++;
        }
        
        x++;
    }
}