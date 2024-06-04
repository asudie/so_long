/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:51:23 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/04 13:47:29 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdlib.h>
# include "my_printf/ft_printf.h"

typedef struct s_game_map
{
	int			map_height;
	int			map_length;
	int			player_position[2];
	int			game_score;
	int			max_score;
	char		**map_data;
	int			game_over;
	int			collectables;
	int			exits;
}				t_game_map;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*textures[7];
	t_game_map	*map;
}				t_data;

int				parse_map(char *file, t_data *data);
int				first_check(char *str);
int				check_walls(char *str);
int				check_one(char *str);
int				check_str(int fd);
int				check_ber(char *str);
int				nl_strlen(char *s);
int				check_paths(int pos_x, int pos_y, char **map_check,
					t_data *data);
int				check_items(t_game_map *map);
void			draw_map(t_data *data);
void			print_map(t_data *data);
int				on_destroy(t_data *data);
int				on_keypress(int keysym, t_data *data);
void			load_textures(t_data *data, int x);
void			find_exit(t_data *data);
void			up_work(t_data *data);
void			left_work(t_data *data);
void			right_work(t_data *data);
void			down_work(t_data *data);
void			key_work(int keysym, t_data *data);
int				count_size(char *file, t_game_map *my_map);
char			*ft_strcpy(char *dst, char *src);
char			**copy_map(t_game_map *my_map);
void			set_ij(int *i, int *j);
void 			free_map(char **map_check);

#endif