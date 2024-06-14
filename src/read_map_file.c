#include "cub3d.h"

void read_map_file(char *filename, t_map *map_info)
{
    int fd;
    int fd2;
    int i;
    // int map_started;
    int map_row;
    int map_width;
    int map_height;
    char *line;

    fd = open(filename, O_RDONLY);
    if (fd == -1) 
    {
        perror("Error opening map file");
        exit(1);
    }

    fd2 = open(filename, O_RDONLY);
    if (fd2 == -1) 
    {
        perror("Error opening map file");
        close(fd);
        exit(1);
    }

    line = NULL;
    i = 0;
    // map_started = 0;
    map_row = 0;
    map_width = 0;
    map_height = 0;

    // First pass: determine map dimensions
    while ((line = get_next_line(fd)) != NULL) 
    {
        if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1')) 
        {
            map_height++;
            if (ft_strlen(line) > map_width) 
            {
                map_width = ft_strlen(line);
            }
        }
        free(line);
    }

    allocate_map(map_info, map_width, map_height);

    // Second pass: read map data
    while ((line = get_next_line(fd2)) != NULL) 
    {
        if (ft_strncmp(line, "NO ", 3) == 0) 
        {
            map_info->north_texture = ft_strdup(ft_strchr(line, ' ') + 1);
            map_info->north_texture[ft_strlen(map_info->north_texture) - 1] = '\0'; // Remove newline
        } 
        else if (ft_strncmp(line, "SO ", 3) == 0) 
        {
            map_info->south_texture = ft_strdup(ft_strchr(line, ' ') + 1);
            map_info->south_texture[ft_strlen(map_info->south_texture) - 1] = '\0';
        } 
        else if (ft_strncmp(line, "WE ", 3) == 0) 
        {
            map_info->west_texture = ft_strdup(ft_strchr(line, ' ') + 1);
            map_info->west_texture[ft_strlen(map_info->west_texture) - 1] = '\0';
        } 
        else if (ft_strncmp(line, "EA ", 3) == 0) 
        {
            map_info->east_texture = ft_strdup(ft_strchr(line, ' ') + 1);
            map_info->east_texture[ft_strlen(map_info->east_texture) - 1] = '\0';
        } 
        else if (ft_strncmp(line, "F ", 2) == 0) 
        {
            map_info->floor_color = get_color(ft_strchr(line, ' ') + 1);
        } 
        else if (ft_strncmp(line, "C ", 2) == 0) 
        {
            map_info->ceiling_color = get_color(ft_strchr(line, ' ') + 1);
        } 
        else if (line[0] == ' ' || (line[0] >= '0' && line[0] <= '1')) 
        {
            i = 0;
            while (i < ft_strlen(line) && line[i] != '\n') 
            {
                if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W') 
                {
                    map_info->player_start_x = map_row;
                    map_info->player_start_y = i;
                    map_info->player_start_dir = line[i];
                    map_info->map[map_row][i] = 0;
                } 
                else if (line[i] == '1') 
                {
                    map_info->map[map_row][i] = 1;
                } 
                else if (line[i] == '0') 
                {
                    map_info->map[map_row][i] = 0;
                } 
                else 
                {
                    map_info->map[map_row][i] = -1;
                }
                i++;
            }
            map_row++;
        }
        free(line);
    }
    close(fd);
    close(fd2);
    
    // for (int y = 0; y < map_info->map_height; y++) {
    // for (int x = 0; x < map_info->map_width; x++) {
    //         printf("%d", map_info->map[y][x]);
    //     }
    //     printf("\n");
    // }
}