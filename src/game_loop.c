/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchvatal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:45:29 by tchvatal          #+#    #+#             */
/*   Updated: 2024/06/25 11:45:32 by tchvatal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Move camera
void	turn_left(t_vars *vars, double camera_speed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = vars->dirx;
	vars->dirx = vars->dirx * cos(camera_speed)
		- vars->diry * sin(camera_speed);
	vars->diry = olddirx * sin(camera_speed)
		+ vars->diry * cos(camera_speed);
	oldplanex = vars->planex;
	vars->planex = vars->planex * cos(camera_speed)
		- vars->planey * sin(camera_speed);
	vars->planey = oldplanex * sin(camera_speed)
		+ vars->planey * cos(camera_speed);
}

void	turn_right(t_vars *vars, double camera_speed)
{
	double	olddirx;
	double	oldplanex;

	olddirx = vars->dirx;
	vars->dirx = vars->dirx * cos(-camera_speed)
		- vars->diry * sin(-camera_speed);
	vars->diry = olddirx * sin(-camera_speed)
		+ vars->diry * cos(-camera_speed);
	oldplanex = vars->planex;
	vars->planex = vars->planex * cos(-camera_speed)
		- vars->planey * sin(-camera_speed);
	vars->planey = oldplanex * sin(-camera_speed)
		+ vars->planey * cos(-camera_speed);
}

int	game_loop(t_vars *vars)
{
	double	move_speed;
	double	camera_speed;

	move_speed = MOVES_SPEED;
	camera_speed = CAMERA_SPEED;
	if (vars->move_forward)
		move_forward(vars, move_speed);
	if (vars->move_backward)
		move_backward(vars, move_speed);
	if (vars->move_left)
		move_left(vars, move_speed);
	if (vars->move_right)
		move_right(vars, move_speed);
	if (vars->turn_left)
		turn_left(vars, camera_speed);
	if (vars->turn_right)
		turn_right(vars, camera_speed);
	mlx_clear_window(vars->mlx, vars->win);
	sky_and_floor(vars);
	raycasting(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}
