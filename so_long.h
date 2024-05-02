#ifndef SO_LONG_H
# define SO_LONG_H

// #include "minilibx_opengl_20191021/mlx.h"
#include "gnl/get_next_line.h"
#include "libft/libft.h"
#include <stdio.h> // DELETE
#include <fcntl.h>
// #include "mlx/mlx.h"
#include <stdlib.h>
// #include <X11/X.h>
// #include <X11/keysym.h>

typedef struct s_game_map
{
    int     map_height;
    int     map_length;
    int     player_position[2];
    int     game_score;
    int     max_score;
    char    **map_data;
    int     game_over;
    int     steps;
    void    *end_img;
    void    *wall;
    void    *exit;
    void    *player;
    void    *floor;
    void    *items;
}   t_game_map;

typedef struct s_data
{
	void		*mlx_ptr; // MLX pointer
	void		*win_ptr; // MLX window pointer
	void		*textures[5]; // MLX image pointers (on the stack)
	t_game_map		*map; // Map pointer (contains map details - preferably kept on the stack)
}	t_data;

int parse_map(char *file, t_game_map *my_map);
int first_check(char *str);
int check_walls(char *str);
int check_one(char *str);
int check_str(int fd);
int check_ber(char *str);
int check_ber(char *str);
int nl_strlen(char *s);
int check_paths(t_game_map *my_map);
int check_items(t_game_map *map);

#endif