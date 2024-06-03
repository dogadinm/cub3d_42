#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "./minilibx-linux/mlx.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PLAYER_RADIUS 0.2 // Player collision

typedef struct  s_img 
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}               t_img;

typedef struct  s_map 
{
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int floor_color;
    int ceiling_color;
    int **map;
    int map_width;
    int map_height;
    int player_start_x;
    int player_start_y;
    char player_start_dir;
}               t_map;

typedef struct  s_vars 
{
    void    *mlx;
    void    *win;
    t_img   img;
    t_img   textures[4];
    double  posX;
    double  posY;
    double  dirX;
    double  dirY;
    double  planeX;
    double  planeY;
    int     move_forward;
    int     move_backward;
    int     move_left;
    int     move_right;
    int     turn_left;
    int     turn_right;
    t_map   map_info;
}               t_vars;

int parse_int(char **line)
{
    int value;
    value = 0;

    while (**line >= '0' && **line <= '9') 
    {
        value = value * 10 + (**line - '0');
        (*line)++;
    }
    return value;
}

int get_color(char *line) 
{
    int r;
    int g;
    int b;

    r = 0;
    g = 0;
    b = 0;

    r = parse_int(&line);
    if (*line != ',') 
    {
        ft_printf("Wrong color\n");
        exit(1);
    }
    line++;  // Skip comma
    g = parse_int(&line);
    if (*line != ',') 
    {
        ft_printf("Wrong color\n");
        exit(1);
    } 
    line++;  
    b = parse_int(&line);
    if (*line != '\0' && *line != '\n')
    {
        ft_printf("Wrong color\n");
        exit(1);
    }
    return (r << 16 | g << 8 | b);
}

void allocate_map(t_map *map_info, int width, int height) 
{
    int i; 
    int j;

    map_info->map_width = width;
    map_info->map_height = height;
    map_info->map = malloc(height * sizeof(int *));
    
    i = 0;
    while (i < height) 
    {
        map_info->map[i] = malloc(width * sizeof(int));
        j = 0;
        while (j < width) 
        {
            map_info->map[i][j] = -1; // Initialize with -1 (undefined)
            j++;
        }
        i++;
    }
}

void free_map(t_map *map_info) 
{
    int i;

    i = 0;
    while (i < map_info->map_height) 
    {
        free(map_info->map[i]);
        i++;
    }
    free(map_info->map);
    free(map_info->north_texture);
    free(map_info->south_texture);
    free(map_info->west_texture);
    free(map_info->east_texture);
}

void check_walls(t_map *g, int i, int j) 
{
    // Checking map boundaries
    if (i == 0 || i == g->map_width - 1 || j == 0 || j == g->map_height - 1) 
    {
        ft_printf("Map is not closed at (%d, %d)\n", j, i);
        free_map(g);
        exit(1);
    }

    // Checking neighboring elements
    if (g->map[j][i] == 0) 
    {
        if (g->map[j - 1][i] == -1 || g->map[j + 1][i] == -1 ||
            g->map[j][i - 1] == -1 || g->map[j][i + 1] == -1) 
        {
            ft_printf("Map is not closed at (%d, %d)\n", j, i);
            free_map(g);
            exit(1);
        }
    }
}

void check_elements(t_map *g) 
{
    int i;
    int j;

    j = 0;
    while (j < g->map_height) 
    {
        i = 0;
        while (i < g->map_width) 
        {
            if (g->map[j][i] == 0) 
            {
                check_walls(g, i, j);
            }
            i++;
        }
        j++;
    }
}

void read_map_file(char *filename, t_map *map_info) 
{
    int fd;
    int fd2;
    int i;
    int map_started;
    int map_row;
    int map_width;
    int map_height;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {
        perror("Error opening map file");
        exit(1);
    }

    fd2 = open(filename, O_RDONLY);
    if (fd2 == -1) 
    {
        perror("Error opening map file");
        close(fd);
        exit(1);
    }

    line = NULL;
    i = 0;
    map_started = 0;
    map_row = 0;
    map_width = 0;
    map_height = 0;

    // First pass: determine map dimensions
    while ((line = get_next_line(fd)) != NULL) 
    {
        if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1')) 
        {
            map_height++;
            if (ft_strlen(line) > map_width) 
            {
                map_width = ft_strlen(line);
            }
        }
        free(line);
    }

    allocate_map(map_info, map_width, map_height);

    // Second pass: read map data
    while ((line = get_next_line(fd2)) != NULL) 
    {
        if (ft_strncmp(line, "NO ", 3) == 0) 
        {
            map_info->north_texture = ft_strdup(ft_strchr(line, ' ') + 1);
            map_info->north_texture[ft_strlen(map_info->north_texture) - 1] = '\0'; // Remove newline
        } 
        else if (ft_strncmp(line, "SO ", 3) == 0) 
        {
            map_info->south_texture = strdup(ft_strchr(line, ' ') + 1);
            map_info->south_texture[ft_strlen(map_info->south_texture) - 1] = '\0';
        } 
        else if (ft_strncmp(line, "WE ", 3) == 0) 
        {
            map_info->west_texture = ft_strdup(ft_strchr(line, ' ') + 1);
            map_info->west_texture[ft_strlen(map_info->west_texture) - 1] = '\0';
        } 
        else if (ft_strncmp(line, "EA ", 3) == 0) 
        {
            map_info->east_texture = ft_strdup(ft_strchr(line, ' ') + 1);
            map_info->east_texture[ft_strlen(map_info->east_texture) - 1] = '\0';
        } 
        else if (ft_strncmp(line, "F ", 2) == 0) 
        {
            map_info->floor_color = get_color(ft_strchr(line, ' ') + 1);
        } 
        else if (ft_strncmp(line, "C ", 2) == 0) 
        {
            map_info->ceiling_color = get_color(ft_strchr(line, ' ') + 1);
        } 
        else if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1')) 
        {
            i = 0;
            while (i < ft_strlen(line) && line[i] != '\n') 
            {
                if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') 
                {
                    map_info->player_start_x = map_row;
                    map_info->player_start_y = i;
                    map_info->player_start_dir = line[i];
                    map_info->map[map_row][i] = 0;
                } 
                else if (line[i] == '1') 
                {
                    map_info->map[map_row][i] = 1;
                } 
                else if (line[i] == '0') 
                {
                    map_info->map[map_row][i] = 0;
                } 
                else 
                {
                    map_info->map[map_row][i] = -1;
                }
                i++;
            }
            map_row++;
        }
        free(line);
    }
    close(fd);
    close(fd2);
    
    for (int y = 0; y < map_info->map_height; y++) {
    for (int x = 0; x < map_info->map_width; x++) {
            printf("%d", map_info->map[y][x]);
        }
        printf("\n");
    }
}

void load_texture(t_vars *vars, t_img *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(vars->mlx, path, &texture->width, &texture->height);
    if (!texture->img) 
    {
        ft_printf("Failed to load texture: %s\n", path);
        exit(1);
    }
    texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, &texture->line_length, &texture->endian);
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}

void draw_line(t_vars *vars, int x, int start, int end, int color)
{
    int y;

    y = start;
    while (y < end) 
    {
        my_mlx_pixel_put(&vars->img, x, y, color);
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

void destroy_images(t_vars *vars) {
    int i;

    i = 0;
    while (i < 4) 
    {
        if (vars->textures[i].img) 
        {
            mlx_destroy_image(vars->mlx, vars->textures[i].img);
        }
        i++;
    }
    if (vars->img.img) 
    {
        mlx_destroy_image(vars->mlx, vars->img.img);
    }
    if (vars->win) 
    {
        mlx_destroy_window(vars->mlx, vars->win);
    }
    if (vars->mlx) 
    {
        mlx_destroy_display(vars->mlx);
        free(vars->mlx);
    }
}

int handle_key_press(int key, t_vars *vars)
{
    if (key == 65307) // Esc key
    {
        free_map(&vars->map_info);
        destroy_images(vars);
        exit(0);
    }
    if (key == 119) // W key
        vars->move_forward = 1;
    if (key == 115) // S key
        vars->move_backward = 1;
    if (key == 97) // A key
        vars->move_left = 1;
    if (key == 100) // D key
        vars->move_right = 1;
    if (key == 65361) // Left arrow key
        vars->turn_left = 1;
    if (key == 65363) // Right arrow key
        vars->turn_right = 1;
    return (0);
}

int handle_key_release(int key, t_vars *vars)
{
    if (key == 119) // W key
        vars->move_forward = 0;
    if (key == 115) // S key
        vars->move_backward = 0;
    if (key == 97) // A key
        vars->move_left = 0;
    if (key == 100) // D key
        vars->move_right = 0;
    if (key == 65361) // Left arrow key
        vars->turn_left = 0;
    if (key == 65363) // Right arrow key
        vars->turn_right = 0;
    return (0);
}

int is_walkable(t_map *map, double x, double y) 
{
    // Checking the center point
    if (map->map[(int)x][(int)y] != 0)
        return 0;

    // Checking points around the center taking into account the player's radius
    if (map->map[(int)(x - PLAYER_RADIUS)][(int)(y - PLAYER_RADIUS)] != 0)
        return 0;
    if (map->map[(int)(x + PLAYER_RADIUS)][(int)(y - PLAYER_RADIUS)] != 0)
        return 0;
    if (map->map[(int)(x - PLAYER_RADIUS)][(int)(y + PLAYER_RADIUS)] != 0)
        return 0;
    if (map->map[(int)(x + PLAYER_RADIUS)][(int)(y + PLAYER_RADIUS)] != 0)
        return 0;

    return 1;
}

int game_loop(t_vars *vars)
{
    double moveSpeed; 
    double rotSpeed;
    double newPosX;
    double newPosY;
    double oldDirX; 
    double oldPlaneX;

    moveSpeed = 0.05; // Move speed
    rotSpeed = 0.03;  // Camera speed

    if (vars->move_forward)
    {
        newPosX = vars->posX + vars->dirX * moveSpeed;
        newPosY = vars->posY + vars->dirY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->move_backward)
    {
        newPosX = vars->posX - vars->dirX * moveSpeed;
        newPosY = vars->posY - vars->dirY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->move_left)
    {
        newPosX = vars->posX - vars->planeX * moveSpeed;
        newPosY = vars->posY - vars->planeY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->move_right)
    {
        newPosX = vars->posX + vars->planeX * moveSpeed;
        newPosY = vars->posY + vars->planeY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->turn_left)
    {
        oldDirX = vars->dirX;
        vars->dirX = vars->dirX * cos(rotSpeed) - vars->dirY * sin(rotSpeed);
        vars->dirY = oldDirX * sin(rotSpeed) + vars->dirY * cos(rotSpeed);
        oldPlaneX = vars->planeX;
        vars->planeX = vars->planeX * cos(rotSpeed) - vars->planeY * sin(rotSpeed);
        vars->planeY = oldPlaneX * sin(rotSpeed) + vars->planeY * cos(rotSpeed);
    }
    if (vars->turn_right)
    {
        oldDirX = vars->dirX;
        vars->dirX = vars->dirX * cos(-rotSpeed) - vars->dirY * sin(-rotSpeed);
        vars->dirY = oldDirX * sin(-rotSpeed) + vars->dirY * cos(-rotSpeed);
        oldPlaneX = vars->planeX;
        vars->planeX = vars->planeX * cos(-rotSpeed) - vars->planeY * sin(-rotSpeed);
        vars->planeY = oldPlaneX * sin(-rotSpeed) + vars->planeY * cos(-rotSpeed);
    }
    mlx_clear_window(vars->mlx, vars->win);
    raycasting(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return (0);
}

int close_window(t_vars *vars) 
{
    free_map(&vars->map_info);
    destroy_images(vars);
    exit(0);
    return (0);
}

void	check_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error\nShould be ./cub3d \"map_file\"\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		ft_printf("Error\nFile must be of type \".cub\"\n");
		exit(1);
	}
}

int main(int argc, char **argv)
{
    t_vars vars;
    check_arg(argc, argv);
    read_map_file(argv[1], &vars.map_info);
    check_elements(&vars.map_info);

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting");
    vars.img.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bpp, &vars.img.line_length, &vars.img.endian);
    
    load_texture(&vars, &vars.textures[0], vars.map_info.north_texture);
    load_texture(&vars, &vars.textures[1], vars.map_info.south_texture);
    load_texture(&vars, &vars.textures[2], vars.map_info.west_texture);
    load_texture(&vars, &vars.textures[3], vars.map_info.east_texture);

    // Set the player's starting position and direction based on map data
    vars.posX = vars.map_info.player_start_x + 0.5; // Start in the center of the tile
    vars.posY = vars.map_info.player_start_y + 0.5; // Start in the center of the tile
    if (vars.map_info.player_start_dir == 'N') 
    {
        vars.dirX = -1; vars.dirY = 0;
        vars.planeX = 0; vars.planeY = 0.66;
    } 
    else if (vars.map_info.player_start_dir == 'S') 
    {
        vars.dirX = 1; vars.dirY = 0;
        vars.planeX = 0; vars.planeY = -0.66;
    } 
    else if (vars.map_info.player_start_dir == 'E') 
    {
        vars.dirX = 0; vars.dirY = 1;
        vars.planeX = 0.66; vars.planeY = 0;
    } 
    else if (vars.map_info.player_start_dir == 'W') 
    {
        vars.dirX = 0; vars.dirY = -1;
        vars.planeX = -0.66; vars.planeY = 0;
    }

    vars.move_forward = 0;
    vars.move_backward = 0;
    vars.move_left = 0;
    vars.move_right = 0;
    vars.turn_left = 0;
    vars.turn_right = 0;

    raycasting(&vars);
    mlx_hook(vars.win, 2, 1L<<0, handle_key_press, &vars);
    mlx_hook(vars.win, 3, 1L<<1, handle_key_release, &vars); 
    mlx_hook(vars.win, 17, 0L, close_window, &vars); 
    mlx_loop_hook(vars.mlx, game_loop, &vars);
    mlx_loop(vars.mlx);
    free_map(&vars.map_info);

    return (0);
}