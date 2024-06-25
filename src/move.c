/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchvatal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:50:53 by tchvatal          #+#    #+#             */
/*   Updated: 2024/06/25 11:50:56 by tchvatal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_key_press(int key, t_vars *vars)
{
	if (key == 65307)
		close_window(vars);
	if (key == 119)
		vars->move_forward = 1;
	if (key == 115)
		vars->move_backward = 1;
	if (key == 97)
		vars->move_left = 1;
	if (key == 100)
		vars->move_right = 1;
	if (key == 65361)
		vars->turn_left = 1;
	if (key == 65363)
		vars->turn_right = 1;
	return (0);
}

int	handle_key_release(int key, t_vars *vars)
{
	if (key == 119)
		vars->move_forward = 0;
	if (key == 115)
		vars->move_backward = 0;
	if (key == 97)
		vars->move_left = 0;
	if (key == 100)
		vars->move_right = 0;
	if (key == 65361)
		vars->turn_left = 0;
	if (key == 65363)
		vars->turn_right = 0;
	return (0);
}

void	init_move(t_vars *vars)
{
	vars->move_forward = 0;
	vars->move_backward = 0;
	vars->move_left = 0;
	vars->move_right = 0;
	vars->turn_left = 0;
	vars->turn_right = 0;
}
