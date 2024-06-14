#include "cub3d.h"

int handle_key_press(int key, t_vars *vars)
{
    if (key == 65307) // Esc key
    {
        free_map(&vars->map_info);
        destroy_images(vars);
        exit(0);
    }
    if (key == 119) // W key
        vars->move_forward = 1;
    if (key == 115) // S key
        vars->move_backward = 1;
    if (key == 97) // A key
        vars->move_left = 1;
    if (key == 100) // D key
        vars->move_right = 1;
    if (key == 65361) // Left arrow key
        vars->turn_left = 1;
    if (key == 65363) // Right arrow key
        vars->turn_right = 1;
    return (0);
}

int handle_key_release(int key, t_vars *vars)
{
    if (key == 119) // W key
        vars->move_forward = 0;
    if (key == 115) // S key
        vars->move_backward = 0;
    if (key == 97) // A key
        vars->move_left = 0;
    if (key == 100) // D key
        vars->move_right = 0;
    if (key == 65361) // Left arrow key
        vars->turn_left = 0;
    if (key == 65363) // Right arrow key
        vars->turn_right = 0;
    return (0);
}

void init_move(t_vars *vars)
{
    vars->move_forward = 0;
    vars->move_backward = 0;
    vars->move_left = 0;
    vars->move_right = 0;
    vars->turn_left = 0;
    vars->turn_right = 0;    
}