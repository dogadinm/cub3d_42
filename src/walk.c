/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:18:44 by mdogadin          #+#    #+#             */
/*   Updated: 2024/06/25 11:56:34 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(t_map *map, double x, double y)
{
	if (map->map[(int)x][(int)y] != 0)
		return (0);
	if (map->map[(int)(x - PLAYER_RADIUS)][(int)(y - PLAYER_RADIUS)] != 0)
		return (0);
	if (map->map[(int)(x + PLAYER_RADIUS)][(int)(y - PLAYER_RADIUS)] != 0)
		return (0);
	if (map->map[(int)(x - PLAYER_RADIUS)][(int)(y + PLAYER_RADIUS)] != 0)
		return (0);
	if (map->map[(int)(x + PLAYER_RADIUS)][(int)(y + PLAYER_RADIUS)] != 0)
		return (0);
	return (1);
}

void	move_forward(t_vars *vars, double move_speed)
{
	double	new_posx;
	double	new_posy;

	new_posx = vars->posx + vars->dirx * move_speed;
	new_posy = vars->posy + vars->diry * move_speed;
	if (is_walkable(&vars->map_info, new_posx, vars->posy))
		vars->posx = new_posx;
	if (is_walkable(&vars->map_info, vars->posx, new_posy))
		vars->posy = new_posy;
}

void	move_backward(t_vars *vars, double move_speed)
{
	double	new_posx;
	double	new_posy;

	new_posx = vars->posx - vars->dirx * move_speed;
	new_posy = vars->posy - vars->diry * move_speed;
	if (is_walkable(&vars->map_info, new_posx, vars->posy))
		vars->posx = new_posx;
	if (is_walkable(&vars->map_info, vars->posx, new_posy))
		vars->posy = new_posy;
}

void	move_left(t_vars *vars, double move_speed)
{
	double	new_posx;
	double	new_posy;

	new_posx = vars->posx - vars->planex * move_speed;
	new_posy = vars->posy - vars->planey * move_speed;
	if (is_walkable(&vars->map_info, new_posx, vars->posy))
		vars->posx = new_posx;
	if (is_walkable(&vars->map_info, vars->posx, new_posy))
		vars->posy = new_posy;
}

void	move_right(t_vars *vars, double move_speed)
{
	double	new_posx;
	double	new_posy;

	new_posx = vars->posx + vars->planex * move_speed;
	new_posy = vars->posy + vars->planey * move_speed;
	if (is_walkable(&vars->map_info, new_posx, vars->posy))
		vars->posx = new_posx;
	if (is_walkable(&vars->map_info, vars->posx, new_posy))
		vars->posy = new_posy;
}
