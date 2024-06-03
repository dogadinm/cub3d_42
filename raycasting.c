#include "cub3d.h"
void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
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
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;
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

    // Draw sky (upper half)
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

    x = 0;
    while (x < SCREEN_WIDTH)
    {

        cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        rayDirX = vars->dirX + vars->planeX * cameraX;
        rayDirY = vars->dirY + vars->planeY * cameraX;

        mapX = (int)vars->posX;
        mapY = (int)vars->posY;

        deltaDistX = fabs(1 / rayDirX);
        deltaDistY = fabs(1 / rayDirY);

        hit = 0;
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (vars->posX - mapX) * deltaDistX;
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

        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (vars->map_info.map[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0)
            perpWallDist = (mapX - vars->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - vars->posY + (1 - stepY) / 2) / rayDirY;

        lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) 
            drawStart = 0;
        drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) 
            drawEnd = SCREEN_HEIGHT - 1;

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

        texX = (int)(wallX * (double)(texture->width));
        if (side == 0 && rayDirX > 0) 
            texX = texture->width - texX - 1;
        if (side == 1 && rayDirY < 0) 
            texX = texture->width - texX - 1;

        y = drawStart;
        while (y < drawEnd)
        {
            d = y * 256 - SCREEN_HEIGHT * 128 + lineHeight * 128;
            texY = ((d * texture->height) / lineHeight) / 256;
            color = *(unsigned int*)(texture->addr + (texY * texture->line_length + texX * (texture->bpp / 8)));
            if (side == 1) 
                color = (color >> 1) & 8355711; // Make color darker for y-sides
            my_mlx_pixel_put(&vars->img, x, y, color);
            y++;
        }
        x++;
    }
}