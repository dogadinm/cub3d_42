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
    int g;
    int b;

    r = 0;
    g = 0;
    b = 0;

    r = parse_int(&line);
    if (*line != ',') 
    {
        ft_printf("Wrong color\n");
        exit(1);
    }
    line++;  // Skip comma
    g = parse_int(&line);
    if (*line != ',') 
    {
        ft_printf("Wrong color\n");
        exit(1);
    } 
    line++;  
    b = parse_int(&line);
    if (*line != '\0' && *line != '\n')
    {
        ft_printf("Wrong color\n");
        exit(1);
    }
    return (r << 16 | g << 8 | b);
}