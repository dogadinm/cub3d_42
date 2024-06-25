/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdogadin <mdogadin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:50:44 by mdogadin          #+#    #+#             */
/*   Updated: 2024/06/25 12:13:40 by mdogadin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error\nShould be ./cub3d \"map_file\"\n");
		exit(1);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
	{
		ft_printf("Error\nFile must be of type \".cub\"\n");
		exit(1);
	}
}

void	init_vars(t_vars *vars)
{
	vars->dirx = 0;
	vars->diry = 0;
	vars->planex = 0;
	vars->planey = 0;
}

void	starting_position(t_vars *vars)
{
	vars->posx = vars->map_info.player_start_x + 0.5;
	vars->posy = vars->map_info.player_start_y + 0.5;
	init_vars(vars);
	if (vars->map_info.player_start_dir == 'N')
	{
		vars->dirx = -1;
		vars->planey = 0.66;
	}
	else if (vars->map_info.player_start_dir == 'S')
	{
		vars->dirx = 1;
		vars->planey = -0.66;
	}
	else if (vars->map_info.player_start_dir == 'E')
	{
		vars->diry = 1;
		vars->planex = 0.66;
	}
	else if (vars->map_info.player_start_dir == 'W')
	{
		vars->diry = -1;
		vars->planex = -0.66;
	}
}

void	creat_window(t_vars *vars)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	vars->img.img = mlx_new_image(vars->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	vars->img.addr = mlx_get_data_addr(vars->img.img, &vars->img.bpp,
			&vars->img.line_length, &vars->img.endian);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	check_arg(argc, argv);
	read_map_file(argv[1], &vars);
	check_elements(&vars.map_info);
	creat_window(&vars);
	ft_load_texture(&vars);
	starting_position(&vars);
	init_move(&vars);
	mlx_hook(vars.win, 2, 1L << 0, handle_key_press, &vars);
	mlx_hook(vars.win, 3, 1L << 1, handle_key_release, &vars);
	mlx_hook(vars.win, 17, 0L, close_window, &vars);
	mlx_loop_hook(vars.mlx, game_loop, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
