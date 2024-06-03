#ifndef CUB3D_H_
#define CUB3D_H_



#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"
#include <math.h>
#include <fcntl.h>


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PLAYER_RADIUS 0.2 // Player collision

typedef struct  s_img 
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_length;
    int     endian;
    int     width;
    int     height;
}               t_img;

typedef struct  s_map 
{
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int floor_color;
    int ceiling_color;
    int **map;
    int map_width;
    int map_height;
    int player_start_x;
    int player_start_y;
    char player_start_dir;
}               t_map;

typedef struct  s_vars 
{
    void    *mlx;
    void    *win;
    t_img   img;
    t_img   textures[4];
    double  posX;
    double  posY;
    double  dirX;
    double  dirY;
    double  planeX;
    double  planeY;
    int     move_forward;
    int     move_backward;
    int     move_left;
    int     move_right;
    int     turn_left;
    int     turn_right;
    t_map   map_info;
}               t_vars;


void raycasting(t_vars *vars);
void ft_load_texture(t_vars *vars);
int game_loop(t_vars *vars);
void read_map_file(char *filename, t_map *map_info);
void check_elements(t_map *g);
int get_color(char *line);
void allocate_map(t_map *map_info, int width, int height);
void free_map(t_map *map_info);
void destroy_images(t_vars *vars);
int close_window(t_vars *vars);
int handle_key_press(int key, t_vars *vars);
int handle_key_release(int key, t_vars *vars);
int get_color(char *line);
void init_move(t_vars *vars);
void allocate_map(t_map *map_info, int width, int height);
#endif