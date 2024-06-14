#include "cub3d.h"

void move_forward(t_vars *vars, double moveSpeed)
{
    double newPosX = vars->posX + vars->dirX * moveSpeed;
    double newPosY = vars->posY + vars->dirY * moveSpeed;
    if (is_walkable(&vars->map_info, newPosX, vars->posY))
        vars->posX = newPosX;
    if (is_walkable(&vars->map_info, vars->posX, newPosY))
        vars->posY = newPosY;
}

void move_backward(t_vars *vars, double moveSpeed)
{
    double newPosX = vars->posX - vars->dirX * moveSpeed;
    double newPosY = vars->posY - vars->dirY * moveSpeed;
    if (is_walkable(&vars->map_info, newPosX, vars->posY))
        vars->posX = newPosX;
    if (is_walkable(&vars->map_info, vars->posX, newPosY))
        vars->posY = newPosY;
}

void move_left(t_vars *vars, double moveSpeed)
{
    double newPosX = vars->posX - vars->planeX * moveSpeed;
    double newPosY = vars->posY - vars->planeY * moveSpeed;
    if (is_walkable(&vars->map_info, newPosX, vars->posY))
        vars->posX = newPosX;
    if (is_walkable(&vars->map_info, vars->posX, newPosY))
        vars->posY = newPosY;
}


void move_right(t_vars *vars, double moveSpeed)
{
    double newPosX = vars->posX + vars->planeX * moveSpeed;
    double newPosY = vars->posY + vars->planeY * moveSpeed;
    if (is_walkable(&vars->map_info, newPosX, vars->posY))
        vars->posX = newPosX;
    if (is_walkable(&vars->map_info, vars->posX, newPosY))
        vars->posY = newPosY;
}