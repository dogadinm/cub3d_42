#include "cub3d.h"

void allocate_map(t_map *map_info)
{
    int i; 
    int j;

    map_info->map = malloc(map_info->map_height * sizeof(int *));
    i = 0;
    while (i < map_info->map_height) 
    {
        map_info->map[i] = malloc(map_info->map_width * sizeof(int));
        j = 0;
        while (j < map_info->map_width) 
        {
            map_info->map[i][j] = -1; // Initialize with -1 (undefined)
            j++;
        }
        i++;
    }
}

void determine_map_dimensions(int fd, t_vars *vars)
{
    char *line;
    vars->map_info.map_height = 0;
    vars->map_info.map_width = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1'))
        {
            (vars->map_info.map_height)++;
            if (ft_strlen(line) > vars->map_info.map_width)
            {
                vars->map_info.map_width = ft_strlen(line);
            }
        }
        free(line);
    }
}

