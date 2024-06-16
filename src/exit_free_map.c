#include "cub3d.h"

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
    free(map_info->ceiling_color);
    free(map_info->floor_color);
    free(map_info->north_texture);
    free(map_info->south_texture);
    free(map_info->west_texture);
    free(map_info->east_texture);
}

void destroy_images(t_vars *vars)
{
    int i;

    i = 0;
    while (i < 4) 
    {
        if (vars->textures[i].img) 
            mlx_destroy_image(vars->mlx, vars->textures[i].img);
        i++;
    }
    if (vars->img.img) 
        mlx_destroy_image(vars->mlx, vars->img.img);
    if (vars->win) 
        mlx_destroy_window(vars->mlx, vars->win);
    if (vars->mlx) 
    {
        mlx_destroy_display(vars->mlx);
        free(vars->mlx);
    }
}

int close_window(t_vars *vars)
{
    free_map(&vars->map_info);
    destroy_images(vars);
    exit(0);
    return (0);
}

void error_exit(t_vars *vars, char *message)
{
    ft_printf("%s\n",message);
    free_map(&vars->map_info);
    destroy_images(vars);
    exit(1);
}
