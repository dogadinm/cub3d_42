/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:43:10 by mdogadin          #+#    #+#             */
/*   Updated: 2024/06/25 11:49:47 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_int(char **line)
{
	int	value;

	value = 0;
	while (**line >= '0' && **line <= '9')
	{
		value = value * 10 + (**line - '0');
		(*line)++;
	}
	return (value);
}

int	get_color(char *line)
{
	int		color;
	t_rgb	rgb;

	if (line == NULL)
		return (-1);
	color = -1;
	rgb.r = parse_int(&line);
	if (*line != ',')
		return (color);
	line++;
	rgb.g = parse_int(&line);
	if (*line != ',')
		return (color);
	line++;
	rgb.b = parse_int(&line);
	if (*line != '\0' && *line != '\n')
		return (color);
	if (rgb.r > 255 || rgb.r < 0 || rgb.g > 255
		|| rgb.g < 0 || rgb.b > 255 || rgb.b < 0)
		return (color);
	color = (rgb.r << 16 | rgb.g << 8 | rgb.b);
	return (color);
}
