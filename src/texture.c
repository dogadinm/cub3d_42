/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:27:15 by mdogadin          #+#    #+#             */
/*   Updated: 2024/06/25 11:29:50 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textures(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		vars->textures[i].img = NULL;
		vars->textures[i].addr = NULL;
		i++;
	}
}

void	load_texture(t_vars *vars, t_img *texture, char *path)
{
	if (path == NULL)
		error_exit(vars, "Failed to load texture");
	texture->img = mlx_xpm_file_to_image(vars->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		error_exit(vars, "Failed to load texture");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_length, &texture->endian);
}

void	ft_load_texture(t_vars *vars)
{
	init_textures(vars);
	load_texture(vars, &vars->textures[0], vars->map_info.north_texture);
	load_texture(vars, &vars->textures[1], vars->map_info.south_texture);
	load_texture(vars, &vars->textures[2], vars->map_info.west_texture);
	load_texture(vars, &vars->textures[3], vars->map_info.east_texture);
}
