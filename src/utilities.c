#include "cub3d.h"

void allocate_map(t_map *map_info, int width, int height)
{
    int i; 
    int j;

    map_info->map_width = width;
    map_info->map_height = height;
    map_info->map = malloc(height * sizeof(int *));
    
    i = 0;
    while (i < height) 
    {
        map_info->map[i] = malloc(width * sizeof(int));
        j = 0;
        while (j < width) 
        {
            map_info->map[i][j] = -1; // Initialize with -1 (undefined)
            j++;
        }
        i++;
    }
}

void determine_map_dimensions(int fd, int *width, int *height)
{
    char *line;
    *width = 0;
    *height = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1'))
        {
            (*height)++;
            if (ft_strlen(line) > *width)
            {
                *width = ft_strlen(line);
            }
        }
        free(line);
    }
}

