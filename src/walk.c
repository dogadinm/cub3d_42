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

void move_forward(t_vars *vars, double moveSpeed)
{
    double newPosX;
    double newPosY;

    newPosX = vars->posX + vars->dirX * moveSpeed;
    newPosY = vars->posY + vars->dirY * moveSpeed;
    if (is_walkable(&vars->map_info, newPosX, vars->posY))
        vars->posX = newPosX;
    if (is_walkable(&vars->map_info, vars->posX, newPosY))
        vars->posY = newPosY;
}

void move_backward(t_vars *vars, double moveSpeed)
{
    double newPosX;
    double newPosY;

    newPosX = vars->posX - vars->dirX * moveSpeed;
    newPosY = vars->posY - vars->dirY * moveSpeed;
    if (is_walkable(&vars->map_info, newPosX, vars->posY))
        vars->posX = newPosX;
    if (is_walkable(&vars->map_info, vars->posX, newPosY))
        vars->posY = newPosY;
}

void move_left(t_vars *vars, double moveSpeed)
{
    double newPosX;
    double newPosY;

    newPosX = vars->posX - vars->planeX * moveSpeed;
    newPosY = vars->posY - vars->planeY * moveSpeed;
    if (is_walkable(&vars->map_info, newPosX, vars->posY))
        vars->posX = newPosX;
    if (is_walkable(&vars->map_info, vars->posX, newPosY))
        vars->posY = newPosY;
}

void move_right(t_vars *vars, double moveSpeed)
{
    double newPosX;
    double newPosY;

    newPosX = vars->posX + vars->planeX * moveSpeed;
    newPosY = vars->posY + vars->planeY * moveSpeed;
    if (is_walkable(&vars->map_info, newPosX, vars->posY))
        vars->posX = newPosX;
    if (is_walkable(&vars->map_info, vars->posX, newPosY))
        vars->posY = newPosY;
}