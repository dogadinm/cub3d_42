/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchvatal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:10:34 by tchvatal          #+#    #+#             */
/*   Updated: 2024/06/25 10:10:41 by tchvatal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	sky_and_floor(t_vars *vars)
{
	int	y;
	int	x;
	int	floor;
	int	ceilling;

	floor = get_color(vars->map_info.floor_color);
	ceilling = get_color(vars->map_info.ceiling_color);
	if (ceilling == -1 || floor == -1)
		error_exit(vars, "Color");
	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			my_mlx_pixel_put(&vars->img, x++, y, ceilling);
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
			my_mlx_pixel_put(&vars->img, x++, y, floor);
		y++;
	}
}

void	calculate_wallx_texx(t_rayc *rayc, t_vars *vars)
{
	double	wallx;

	if (rayc->side == 0)
		wallx = vars->posy + rayc->perp_wall_dist * rayc->ray_diry;
	else
		wallx = vars->posx + rayc->perp_wall_dist * rayc->ray_dirx;
	wallx -= floor(wallx);
	rayc->texx = (int)(wallx * (double)(rayc->texture->width));
	if (rayc->side == 0 && rayc->ray_dirx > 0)
		rayc->texx = rayc->texture->width - rayc->texx - 1;
	if (rayc->side == 1 && rayc->ray_diry < 0)
		rayc->texx = rayc->texture->width - rayc->texx - 1;
}

void	rayc_draw(t_rayc *rayc, t_vars *vars)
{
	int				y;
	int				texy;
	unsigned int	color;
	int				d;

	y = rayc->draw_start;
	while (y < rayc->draw_end)
	{
		d = rayc->texture->height * (y * 2 - SCREEN_HEIGHT + rayc->line_height);
		texy = d / (rayc->line_height * 2);
		color = *(unsigned int *)(rayc->texture->addr
				+ (texy * rayc->texture->line_length
					+ rayc->texx * (rayc->texture->bpp / 8)));
		if (rayc->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(&vars->img, rayc->x, y, color);
		y++;
	}
}

void	raycasting(t_vars *vars)
{
	t_rayc	rayc;

	rayc.x = 0;
	while (rayc.x < SCREEN_WIDTH)
	{
		fill_rayc_variables(&rayc, vars);
		calculate_step_sidedist(&rayc, vars);
		check_wall_hit(&rayc, vars);
		fill_rayc_variables2(&rayc, vars);
		load_rayc_textures(&rayc, vars);
		calculate_wallx_texx(&rayc, vars);
		rayc_draw(&rayc, vars);
		rayc.x++;
	}
}
