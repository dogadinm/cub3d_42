/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:23:02 by mdogadin          #+#    #+#             */
/*   Updated: 2024/06/25 12:16:03 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocate_map(t_map *map_info)
{
	int	i;
	int	j;

	map_info->map = malloc(map_info->map_height * sizeof(int *));
	i = 0;
	while (i < map_info->map_height)
	{
		map_info->map[i] = malloc(map_info->map_width * sizeof(int));
		j = 0;
		while (j < map_info->map_width)
		{
			map_info->map[i][j] = -1;
			j++;
		}
		i++;
	}
}

void	init_map_info(t_vars *vars)
{
	vars->map_info.map = NULL;
	vars->map_info.north_texture = NULL;
	vars->map_info.south_texture = NULL;
	vars->map_info.west_texture = NULL;
	vars->map_info.east_texture = NULL;
	vars->map_info.ceiling_color = NULL;
	vars->map_info.floor_color = NULL;
}

void	determine_map_dimensions(int fd, t_vars *vars)
{
	char	*line;

	vars->map_info.map_height = 0;
	vars->map_info.map_width = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1'))
		{
			(vars->map_info.map_height)++;
			if (ft_strlen(line) > vars->map_info.map_width)
			{
				vars->map_info.map_width = ft_strlen(line);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
}
