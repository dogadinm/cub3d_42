#include "cub3d.h"

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

void ft_load_texture(t_vars *vars)
{
    load_texture(vars, &vars->textures[0], vars->map_info.north_texture);
    load_texture(vars, &vars->textures[1], vars->map_info.south_texture);
    load_texture(vars, &vars->textures[2], vars->map_info.west_texture);
    load_texture(vars, &vars->textures[3], vars->map_info.east_texture);
}