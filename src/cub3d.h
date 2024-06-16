#ifndef CUB3D_H_
#define CUB3D_H_

#include "../libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>
#include <fcntl.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PLAYER_RADIUS 0.2   // Player collision
#define MOVES_SPEED 0.03    // Move speed
#define CAMERA_SPEED 0.01  // Camera speed

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
    char *floor_color;
    char *ceiling_color;
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

// Draw picture
int game_loop(t_vars *vars);
void raycasting(t_vars *vars);

// Read map file
void    check_elements(t_map *g);
void    read_map_file(char *filename, t_vars *vars);
void    determine_map_dimensions(int fd, int *width, int *height);
void    allocate_map(t_map *map_info, int width, int height);
void    free_map(t_map *map_info);

// Load picture
int     get_color(char *line);
void    sky_and_floor(t_vars *vars);
void    ft_load_texture(t_vars *vars);

// Move
int     handle_key_press(int key, t_vars *vars);
int     handle_key_release(int key, t_vars *vars);
void    init_move(t_vars *vars);
void    move_forward(t_vars *vars, double moveSpeed);
void    move_backward(t_vars *vars, double moveSpeed);
void    move_left(t_vars *vars, double moveSpeed);
void    move_right(t_vars *vars, double moveSpeed);

// Close
int     close_window(t_vars *vars);
void    error_exit(t_vars *vars, char *message);

#endif