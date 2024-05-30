#include "./libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PLAYER_RADIUS 0.2 // Толщина игрока

typedef struct  s_img {
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}               t_img;

typedef struct  s_map {
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

typedef struct  s_vars {
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

int get_color(char *line) {
    int r, g, b;
    sscanf(line, "%d,%d,%d", &r, &g, &b);
    return (r << 16 | g << 8 | b);
}

void allocate_map(t_map *map_info, int width, int height) {
    map_info->map_width = width;
    map_info->map_height = height;
    map_info->map = malloc(height * sizeof(int *));
    for (int i = 0; i < height; i++) {
        map_info->map[i] = malloc(width * sizeof(int) - 1);
        for (int j = 0; j < width; j++) {
            map_info->map[i][j] = -1; // Initialize with -1 (undefined)
        }
    }
}

void free_map(t_map *map_info) {
    for (int i = 0; i < map_info->map_height; i++) {
        free(map_info->map[i]);
    }
    free(map_info->map);
    free(map_info->north_texture);
    free(map_info->south_texture);
    free(map_info->west_texture);
    free(map_info->east_texture);
}




void check_walls(t_map *g, int i, int j) {
    // Checking map boundaries
    if (i == 0 || i == g->map_width - 1 || j == 0 || j == g->map_height - 1) {
        ft_printf("Map is not closed at (%d, %d)\n", j, i);
        free_map(g);
        exit(1);
    }

    // Checking neighboring elements
    if (g->map[j][i] == 0) {
        if (g->map[j - 1][i] == -1 || g->map[j + 1][i] == -1 ||
            g->map[j][i - 1] == -1 || g->map[j][i + 1] == -1) {
            ft_printf("Map is not closed at (%d, %d)\n", j, i);
            free_map(g);
         
            exit(1);
        }
    }
}

void check_elements(t_map *g) {
    for (int j = 0; j < g->map_height; j++) {
        for (int i = 0; i < g->map_width; i++) {
            if (g->map[j][i] == 0) {
                check_walls(g, i, j);
            }
        }
    }
}



void read_map_file(char *filename, t_map *map_info) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening map file");
        exit(1);
    }

    int fd2 = open(filename, O_RDONLY);
    if (fd2 == -1) {
        perror("Error opening map file");
        close(fd);
        exit(1);
    }

    char *line = NULL;
    int map_started = 0;
    int map_row = 0;
    int map_width = 0;
    int map_height = 0;

    // First pass: determine map dimensions
    while ((line = get_next_line(fd)) != NULL) {
        if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1')) {
            map_height++;
            if (strlen(line) > map_width) {
                map_width = strlen(line);
            }
        }
        free(line);
    }

    allocate_map(map_info, map_width, map_height);
    lseek(fd2, 0, SEEK_SET);

    // Second pass: read map data
    while ((line = get_next_line(fd2)) != NULL) {
        if (ft_strncmp(line, "NO ", 3) == 0) {
            map_info->north_texture = ft_strdup(ft_strchr(line, ' ') + 1);
            map_info->north_texture[ft_strlen(map_info->north_texture) - 1] = '\0'; // Remove newline
        } else if (ft_strncmp(line, "SO ", 3) == 0) {
            map_info->south_texture = strdup(ft_strchr(line, ' ') + 1);
            map_info->south_texture[ft_strlen(map_info->south_texture) - 1] = '\0';
        } else if (ft_strncmp(line, "WE ", 3) == 0) {
            map_info->west_texture = ft_strdup(ft_strchr(line, ' ') + 1);
            map_info->west_texture[ft_strlen(map_info->west_texture) - 1] = '\0';
        } else if (ft_strncmp(line, "EA ", 3) == 0) {
            map_info->east_texture = strdup(ft_strchr(line, ' ') + 1);
            map_info->east_texture[ft_strlen(map_info->east_texture) - 1] = '\0';
        } else if (ft_strncmp(line, "F ", 2) == 0) {
            map_info->floor_color = get_color(ft_strchr(line, ' ') + 1);
        } else if (ft_strncmp(line, "C ", 2) == 0) {
            map_info->ceiling_color = get_color(ft_strchr(line, ' ') + 1);
        } else if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1')) {
            for (int i = 0; i < ft_strlen(line) && line[i] != '\n'; i++) {
                if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') {
                    map_info->player_start_x = map_row;
                    map_info->player_start_y = i;
                    map_info->player_start_dir = line[i];
                    map_info->map[map_row][i] = 0;
                } else if (line[i] == '1') {
                    map_info->map[map_row][i] = 1;
                } else if (line[i] == '0') {
                    map_info->map[map_row][i] = 0;
                } else {
                    map_info->map[map_row][i] = -1;
                }
            }
            map_row++;
        }
        free(line);
    }
    close(fd);
    close(fd2);
    
    // for (int y = 0; y < map_info->map_height; y++) {
    // for (int x = 0; x < map_info->map_width; x++) {
    //         printf("%d", map_info->map[y][x]);
    //     }
    //     printf("\n");
    // }

    // // Check if map is surrounded by walls
    // for (int i = 0; i < map_info->map_width; i++) {
    //     if (map_info->map[0][i] != 1 || map_info->map[map_info->map_height - 1][i] != 1) {
    //         fprintf(stderr, "Error: Map is not closed/surrounded by walls\n");
    //         exit(1);
    //     }
    // }
    // for (int i = 0; i < map_info->map_height; i++) {
    //     if (map_info->map[i][0] != 1 || map_info->map[i][map_info->map_width - 1] != 1) {
    //         fprintf(stderr, "Error: Map is not closed/surrounded by walls\n");
    //         exit(1);
    //     }
    // }
}

void load_texture(t_vars *vars, t_img *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(vars->mlx, path, &texture->width, &texture->height);
    if (!texture->img) {
        fprintf(stderr, "Failed to load texture: %s\n", path);
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

    for (y = start; y < end; y++)
        my_mlx_pixel_put(&vars->img, x, y, color);
}

void draw_minimap(t_vars *vars)
{
    int map_scale = 5; // масштаб миникарты
    int offset_x = 10; // смещение миникарты от левого края окна
    int offset_y = 10; // смещение миникарты от верхнего края окна

    for (int y = 0; y < vars->map_info.map_height; y++)
    {
        for (int x = 0; x < vars->map_info.map_width; x++)
        {
            int color;
            if (vars->map_info.map[y][x] == 1)
                color = 0xFFFFFF; // белый для стен
            else if (vars->map_info.map[y][x] == 0)
                color = 0x000000; // черный для пола
            else
                continue;

            for (int i = 0; i < map_scale; i++)
            {
                for (int j = 0; j < map_scale; j++)
                {
                    my_mlx_pixel_put(&vars->img, offset_x + x * map_scale + i, offset_y + y * map_scale + j, color);
                }
            }
        }
    }

    // Рисуем игрока на миникарте
    int player_x = offset_x + (int)(vars->posX * map_scale);
    int player_y = offset_y + (int)(vars->posY * map_scale);

    for (int i = 0; i < map_scale; i++)
    {
        for (int j = 0; j < map_scale; j++)
        {
            my_mlx_pixel_put(&vars->img, player_x + i, player_y + j, 0xFF0000); // красный цвет для игрока
        }
    }
}

void raycasting(t_vars *vars)
{
    int x, y;

    // Draw sky (upper half)
    for (y = 0; y < SCREEN_HEIGHT / 2; y++)
    {
        for (x = 0; x < SCREEN_WIDTH; x++)
        {
            my_mlx_pixel_put(&vars->img, x, y, vars->map_info.ceiling_color);
        }
    }

    // Draw floor (lower half)
    for (y = SCREEN_HEIGHT / 2; y < SCREEN_HEIGHT; y++)
    {
        for (x = 0; x < SCREEN_WIDTH; x++)
        {
            my_mlx_pixel_put(&vars->img, x, y, vars->map_info.floor_color);
        }
    }

    for (x = 0; x < SCREEN_WIDTH; x++)
    {
        double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
        double rayDirX = vars->dirX + vars->planeX * cameraX;
        double rayDirY = vars->dirY + vars->planeY * cameraX;

        int mapX = (int)vars->posX;
        int mapY = (int)vars->posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

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

        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

        t_img *texture;
        if (side == 0) {
            if (rayDirX > 0) {
                texture = &vars->textures[0]; // North
            } else {
                texture = &vars->textures[1]; // South
            }
        } else {
            if (rayDirY > 0) {
                texture = &vars->textures[3]; // East
            } else {
                texture = &vars->textures[2]; // West
            }
        }
        
        double wallX;
        if (side == 0) wallX = vars->posY + perpWallDist * rayDirY;
        else           wallX = vars->posX + perpWallDist * rayDirX;
        wallX -= floor(wallX);

        int texX = (int)(wallX * (double)(texture->width));
        if (texX < 0) texX = 0;
        if (texX >= texture->width) texX = texture->width - 1;

        if (side == 0 && rayDirX > 0) texX = texture->width - texX - 1;
        if (side == 1 && rayDirY < 0) texX = texture->width - texX - 1;

        for (int y = drawStart; y < drawEnd; y++)
        {
            int d = y * 256 - SCREEN_HEIGHT * 128 + lineHeight * 128;
            int texY = ((d * texture->height) / lineHeight) / 256;
            if (texY < 0) texY = 0;
            if (texY >= texture->height) texY = texture->height - 1;

            unsigned int color = *(unsigned int*)(texture->addr + (texY * texture->line_length + texX * (texture->bpp / 8)));
            if (side == 1) color = (color >> 1) & 8355711; // Make color darker for y-sides
            my_mlx_pixel_put(&vars->img, x, y, color);
        }
    }

    // Рисуем миникарту
    draw_minimap(vars);
}

int handle_key_press(int key, t_vars *vars)
{
    if (key == 65307) // Esc key
    {
        mlx_destroy_window(vars->mlx, vars->win);
        free_map(&vars->map_info);
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

int is_walkable(t_map *map, double x, double y) {
    // Проверяем центральную точку
    if (map->map[(int)x][(int)y] != 0)
        return 0;

    // Проверяем точки вокруг центра с учетом радиуса игрока
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
    double moveSpeed = 0.05; // Увеличена скорость движения для тестирования
    double rotSpeed = 0.03;  // Увеличена скорость поворота для тестирования

    if (vars->move_forward)
    {
        double newPosX = vars->posX + vars->dirX * moveSpeed;
        double newPosY = vars->posY + vars->dirY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->move_backward)
    {
        double newPosX = vars->posX - vars->dirX * moveSpeed;
        double newPosY = vars->posY - vars->dirY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->move_left)
    {
        double newPosX = vars->posX - vars->planeX * moveSpeed;
        double newPosY = vars->posY - vars->planeY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->move_right)
    {
        double newPosX = vars->posX + vars->planeX * moveSpeed;
        double newPosY = vars->posY + vars->planeY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->turn_left)
    {
        double oldDirX = vars->dirX;
        vars->dirX = vars->dirX * cos(rotSpeed) - vars->dirY * sin(rotSpeed);
        vars->dirY = oldDirX * sin(rotSpeed) + vars->dirY * cos(rotSpeed);
        double oldPlaneX = vars->planeX;
        vars->planeX = vars->planeX * cos(rotSpeed) - vars->planeY * sin(rotSpeed);
        vars->planeY = oldPlaneX * sin(rotSpeed) + vars->planeY * cos(rotSpeed);
    }
    if (vars->turn_right)
    {
        double oldDirX = vars->dirX;
        vars->dirX = vars->dirX * cos(-rotSpeed) - vars->dirY * sin(-rotSpeed);
        vars->dirY = oldDirX * sin(-rotSpeed) + vars->dirY * cos(-rotSpeed);
        double oldPlaneX = vars->planeX;
        vars->planeX = vars->planeX * cos(-rotSpeed) - vars->planeY * sin(-rotSpeed);
        vars->planeY = oldPlaneX * sin(-rotSpeed) + vars->planeY * cos(-rotSpeed);
    }
    mlx_clear_window(vars->mlx, vars->win);
    raycasting(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return (0);
}

int close_window(t_vars *vars) {
    mlx_destroy_window(vars->mlx, vars->win);
    free_map(&vars->map_info);
    exit(0);
    return (0);
}

int main(void)
{
    t_vars vars;

    read_map_file("2.cub", &vars.map_info); // Убедитесь, что указали правильный путь к вашему файлу карты
    check_elements(&vars.map_info);

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Raycasting");
    vars.img.img = mlx_new_image(vars.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bpp, &vars.img.line_length, &vars.img.endian);
    
    // Загружаем текстуры
    load_texture(&vars, &vars.textures[0], vars.map_info.north_texture);
    load_texture(&vars, &vars.textures[1], vars.map_info.south_texture);
    load_texture(&vars, &vars.textures[2], vars.map_info.west_texture);
    load_texture(&vars, &vars.textures[3], vars.map_info.east_texture);

    // Устанавливаем начальную позицию игрока и направление на основе данных карты
    vars.posX = vars.map_info.player_start_x + 0.5; // Start in the center of the tile
    vars.posY = vars.map_info.player_start_y + 0.5; // Start in the center of the tile
    if (vars.map_info.player_start_dir == 'N') {
        vars.dirX = -1; vars.dirY = 0;
        vars.planeX = 0; vars.planeY = 0.66;
    } else if (vars.map_info.player_start_dir == 'S') {
        vars.dirX = 1; vars.dirY = 0;
        vars.planeX = 0; vars.planeY = -0.66;
    } else if (vars.map_info.player_start_dir == 'E') {
        vars.dirX = 0; vars.dirY = 1;
        vars.planeX = -0.66; vars.planeY = 0;
    } else if (vars.map_info.player_start_dir == 'W') {
        vars.dirX = 0; vars.dirY = -1;
        vars.planeX = 0.66; vars.planeY = 0;
    }

    vars.move_forward = 0;
    vars.move_backward = 0;
    vars.move_left = 0;
    vars.move_right = 0;
    vars.turn_left = 0;
    vars.turn_right = 0;

    raycasting(&vars);
    mlx_hook(vars.win, 2, 1L<<0, handle_key_press, &vars); // KeyPress
    mlx_hook(vars.win, 3, 1L<<1, handle_key_release, &vars); // KeyRelease
    mlx_hook(vars.win, 17, 0L, close_window, &vars); // Window close
    mlx_loop_hook(vars.mlx, game_loop, &vars); // Loop
    mlx_loop(vars.mlx);

    return (0);
}