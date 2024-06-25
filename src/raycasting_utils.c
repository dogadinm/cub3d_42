/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchvatal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:31:47 by tchvatal          #+#    #+#             */
/*   Updated: 2024/06/25 10:31:51 by tchvatal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	fill_rayc_variables(t_rayc *rayc, t_vars *vars)
{
	rayc->camerax = 2 * rayc->x / (double)SCREEN_WIDTH - 1;
	rayc->ray_dirx = vars->dirx + vars->planex * rayc->camerax;
	rayc->ray_diry = vars->diry + vars->planey * rayc->camerax;
	rayc->mapx = (int)vars->posx;
	rayc->mapy = (int)vars->posy;
	rayc->delta_distx = fabs(1 / rayc->ray_dirx);
	rayc->delta_disty = fabs(1 / rayc->ray_diry);
}

void	calculate_step_sidedist(t_rayc *rayc, t_vars *vars)
{
	if (rayc->ray_dirx < 0)
	{
		rayc->stepx = -1;
		rayc->side_distx = (vars->posx - rayc->mapx) * rayc->delta_distx;
	}
	else
	{
		rayc->stepx = 1;
		rayc->side_distx = (rayc->mapx + 1.0 - vars->posx) * rayc->delta_distx;
	}
	if (rayc->ray_diry < 0)
	{
		rayc->stepy = -1;
		rayc->side_disty = (vars->posy - rayc->mapy) * rayc->delta_disty;
	}
	else
	{
		rayc->stepy = 1;
		rayc->side_disty = (rayc->mapy + 1.0 - vars->posy) * rayc->delta_disty;
	}
}

void	check_wall_hit(t_rayc *rayc, t_vars *vars)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rayc->side_distx < rayc->side_disty)
		{
			rayc->side_distx += rayc->delta_distx;
			rayc->mapx += rayc->stepx;
			rayc->side = 0;
		}
		else
		{
			rayc->side_disty += rayc->delta_disty;
			rayc->mapy += rayc->stepy;
			rayc->side = 1;
		}
		if (vars->map_info.map[rayc->mapx][rayc->mapy] > 0)
			hit = 1;
	}
}

void	fill_rayc_variables2(t_rayc *rayc, t_vars *vars)
{
	if (rayc->side == 0)
		rayc->perp_wall_dist = (rayc->mapx - vars->posx
				+ (1 - rayc->stepx) / 2) / rayc->ray_dirx;
	else
		rayc->perp_wall_dist = (rayc->mapy - vars->posy
				+ (1 - rayc->stepy) / 2) / rayc->ray_diry;
	rayc->line_height = (int)(SCREEN_HEIGHT / rayc->perp_wall_dist);
	rayc->draw_start = -rayc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rayc->draw_start < 0)
		rayc->draw_start = 0;
	rayc->draw_end = rayc->line_height / 2 + SCREEN_HEIGHT / 2;
	if (rayc->draw_end >= SCREEN_HEIGHT)
		rayc->draw_end = SCREEN_HEIGHT - 1;
}

void	load_rayc_textures(t_rayc *rayc, t_vars *vars)
{
	if (rayc->side == 0)
	{
		if (rayc->ray_dirx > 0)
			rayc->texture = &vars->textures[0];
		else
			rayc->texture = &vars->textures[1];
	}
	else
	{
		if (rayc->ray_diry > 0)
			rayc->texture = &vars->textures[2];
		else
			rayc->texture = &vars->textures[3];
	}
}
