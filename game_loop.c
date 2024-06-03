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


int game_loop(t_vars *vars)
{
    double moveSpeed; 
    double rotSpeed;
    double newPosX;
    double newPosY;
    double oldDirX; 
    double oldPlaneX;

    moveSpeed = 0.05; // Move speed
    rotSpeed = 0.03;  // Camera speed

    if (vars->move_forward)
    {
        newPosX = vars->posX + vars->dirX * moveSpeed;
        newPosY = vars->posY + vars->dirY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->move_backward)
    {
        newPosX = vars->posX - vars->dirX * moveSpeed;
        newPosY = vars->posY - vars->dirY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->move_left)
    {
        newPosX = vars->posX - vars->planeX * moveSpeed;
        newPosY = vars->posY - vars->planeY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->move_right)
    {
        newPosX = vars->posX + vars->planeX * moveSpeed;
        newPosY = vars->posY + vars->planeY * moveSpeed;
        if (is_walkable(&vars->map_info, newPosX, vars->posY))
            vars->posX = newPosX;
        if (is_walkable(&vars->map_info, vars->posX, newPosY))
            vars->posY = newPosY;
    }
    if (vars->turn_left)
    {
        oldDirX = vars->dirX;
        vars->dirX = vars->dirX * cos(rotSpeed) - vars->dirY * sin(rotSpeed);
        vars->dirY = oldDirX * sin(rotSpeed) + vars->dirY * cos(rotSpeed);
        oldPlaneX = vars->planeX;
        vars->planeX = vars->planeX * cos(rotSpeed) - vars->planeY * sin(rotSpeed);
        vars->planeY = oldPlaneX * sin(rotSpeed) + vars->planeY * cos(rotSpeed);
    }
    if (vars->turn_right)
    {
        oldDirX = vars->dirX;
        vars->dirX = vars->dirX * cos(-rotSpeed) - vars->dirY * sin(-rotSpeed);
        vars->dirY = oldDirX * sin(-rotSpeed) + vars->dirY * cos(-rotSpeed);
        oldPlaneX = vars->planeX;
        vars->planeX = vars->planeX * cos(-rotSpeed) - vars->planeY * sin(-rotSpeed);
        vars->planeY = oldPlaneX * sin(-rotSpeed) + vars->planeY * cos(-rotSpeed);
    }
    mlx_clear_window(vars->mlx, vars->win);
    raycasting(vars);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
    return (0);
}
