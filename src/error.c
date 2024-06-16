#include "cub3d.h"

void error_exit(t_vars *vars, char *message)
{
    ft_printf("%s\n",message);
    free_map(&vars->map_info);
    destroy_images(vars);
    exit(1);
}
