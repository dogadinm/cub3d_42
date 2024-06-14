#include "cub3d.h"

int is_walkable(t_map *map, double x, double y)
{
    // Checking the center point
    if (map->map[(int)x][(int)y] != 0)
        return 0;
    // Checking points around the center taking into account the player's radius
    if (map->map[(int)(x - PLAYER_RADIUS)][(int)(y - PLAYER_RADIUS)] != 0)
        return 0;
    if (map->map[(int)(x + PLAYER_RADIUS)][(int)(y - PLAYER_RADIUS)] != 0)
        return 0;
    if (map->map[(int)(x - PLAYER_RADIUS)][(int)(y + PLAYER_RADIUS)] != 0)
        return 0;
    if (map->map[(int)(x + PLAYER_RADIUS)][(int)(y + PLAYER_RADIUS)] != 0)
        return 0;
    return 1;
}

// Move camera
void turn_left(t_vars *vars, double cameraSpeed)
{
    double oldDirX = vars->dirX;
    vars->dirX = vars->dirX * cos(cameraSpeed) - vars->dirY * sin(cameraSpeed);
    vars->dirY = oldDirX * sin(cameraSpeed) + vars->dirY * cos(cameraSpeed);
    double oldPlaneX = vars->planeX;
    vars->planeX = vars->planeX * cos(cameraSpeed) - vars->planeY * sin(cameraSpeed);
    vars->planeY = oldPlaneX * sin(cameraSpeed) + vars->planeY * cos(cameraSpeed);
}

void turn_right(t_vars *vars, double cameraSpeed)
{
    double oldDirX = vars->dirX;
    vars->dirX = vars->dirX * cos(-cameraSpeed) - vars->dirY * sin(-cameraSpeed);
    vars->dirY = oldDirX * sin(-cameraSpeed) + vars->dirY * cos(-cameraSpeed);
    double oldPlaneX = vars->planeX;
    vars->planeX = vars->planeX * cos(-cameraSpeed) - vars->planeY * sin(-cameraSpeed);
    vars->planeY = oldPlaneX * sin(-cameraSpeed) + vars->planeY * cos(-cameraSpeed);
}

int game_loop(t_vars *vars)
{
    double moveSpeed = MOVES_SPEED;
    double cameraSpeed = CAMERA_SPEED;

    if (vars->move_forward)
        move_forward(vars, moveSpeed);
    if (vars->move_backward)
        move_backward(vars, moveSpeed);
    if (vars->move_left)
        move_left(vars, moveSpeed);
    if (vars->move_right)
        move_right(vars, moveSpeed);
    if (vars->turn_left)
        turn_left(vars, cameraSpeed);
    if (vars->turn_right)
        turn_right(vars, cameraSpeed);

    mlx_clear_window(vars->mlx, vars->win);
    sky_and_floor(vars);
    raycasting(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return (0);
}