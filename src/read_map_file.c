/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:30:03 by mdogadin          #+#    #+#             */
/*   Updated: 2024/06/25 13:42:19 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_info(char *line, char *info, t_vars *vars)
{
	if (info != NULL)
		free(info);
	info = ft_strtrim(ft_strdup(ft_strchr(line, ' ') + 1), " ");
	if (!info)
	{
		free(line);
		error_exit(vars, "Memory allocation failed for read_map_file");
	}
	info[ft_strlen(info) - 1] = '\0';
	return (info);
}

void	read_map_metadata(char *line, t_map *map_info, t_vars *vars)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		map_info->north_texture = get_texture_info
			(line, map_info->north_texture, vars);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map_info->south_texture = get_texture_info
			(line, map_info->south_texture, vars);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map_info->west_texture = get_texture_info
			(line, map_info->west_texture, vars);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map_info->east_texture = get_texture_info
			(line, map_info->east_texture, vars);
	else if (ft_strncmp(line, "F ", 2) == 0)
		map_info->floor_color = get_texture_info
			(line, map_info->floor_color, vars);
	else if (ft_strncmp(line, "C ", 2) == 0)
		map_info->ceiling_color = get_texture_info
			(line, map_info->ceiling_color, vars);
}

void	parse_map_line(char *line, t_map *map_info, int map_row)
{
	int	i;

	i = 0;
	while (i < ft_strlen(line) && line[i] != '\n')
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
		{
			map_info->player_start_x = map_row;
			map_info->player_start_y = i;
			map_info->player_start_dir = line[i];
			map_info->map[map_row][i] = 0;
			map_info->players++;
		}
		else if (line[i] == '1')
			map_info->map[map_row][i] = 1;
		else if (line[i] == '0')
			map_info->map[map_row][i] = 0;
		else
			map_info->map[map_row][i] = -1;
		i++;
	}
}

void	read_map_data(int fd, t_map *map_info, t_vars *vars)
{
	char	*line;
	int		map_row;

	map_row = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		read_map_metadata(line, map_info, vars);
		if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1'))
		{
			parse_map_line(line, map_info, map_row);
			map_row++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

void	read_map_file(char *filename, t_vars *vars)
{
	int	fd1;
	int	fd2;

	init_map_info(vars);
	vars->map_info.players = 0;
	fd1 = open(filename, O_RDONLY);
	if (fd1 == -1)
	{
		write(2, "Error opening map file\n", 23);
		exit(1);
	}
	fd2 = open(filename, O_RDONLY);
	if (fd2 == -1)
	{
		close(fd1);
		write(2, "Error opening map file\n", 23);
		exit (1);
	}
	determine_map_dimensions(fd1, vars);
	allocate_map(&vars->map_info);
	read_map_data(fd2, &vars->map_info, vars);
	close(fd1);
	close(fd2);
}
