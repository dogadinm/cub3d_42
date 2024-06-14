#include "cub3d.h"

void check_walls(t_map *g, int i, int j) 
{
    // Checking map boundaries
    if (i == 0 || i == g->map_width - 1 || j == 0 || j == g->map_height - 1) 
    {
        ft_printf("Map is not closed at (%d, %d)\n", j, i);
        free_map(g);
        exit(1);
    }

    // Checking neighboring elements
    if (g->map[j][i] == 0) 
    {
        if (g->map[j - 1][i] == -1 || g->map[j + 1][i] == -1 ||
            g->map[j][i - 1] == -1 || g->map[j][i + 1] == -1) 
        {
            ft_printf("Map is not closed at (%d, %d)\n", j, i);
            free_map(g);
            exit(1);
        }
    }
}

void check_elements(t_map *g)
{
    int i;
    int j;

    j = 0;
    while (j < g->map_height) 
    {
        i = 0;
        while (i < g->map_width) 
        {
            if (g->map[j][i] == 0) 
            {
                check_walls(g, i, j);
            }
            i++;
        }
        j++;
    }
}
