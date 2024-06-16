#include "cub3d.h"

int parse_int(char **line)
{
    int value;
    value = 0;

    while (**line >= '0' && **line <= '9') 
    {
        value = value * 10 + (**line - '0');
        (*line)++;
    }
    return value;
}

int get_color(char *line) 
{
    int r;
    int b;
    int g;
    int color;

    if (line == NULL)
        return (-1);
    r = 0;
    g = 0;
    b = 0;
    color = -1; // Initialize with error code
    r = parse_int(&line);
    if (*line != ',') 
        return color;
    line++;  // Skip comma
    g = parse_int(&line);
    if (*line != ',') 
        return color;
    line++;  
    b = parse_int(&line);
    if (*line != '\0' && *line != '\n')
        return color;
    if (r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0)
        return color;
    color = (r << 16 | g << 8 | b);
    return color;
}
