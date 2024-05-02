#include "so_long.h"

void count_size(char *file, t_game_map *my_map)
{
	int fd;
	char *temp_str;
	int i;

	fd = open(file, O_RDONLY);
	i = 0;
	temp_str = get_next_line(fd);
	my_map->map_length = nl_strlen(temp_str);
	while(temp_str != NULL)
	{
		i++;
		temp_str = get_next_line(fd);
	}	
	my_map->map_height = i;
	close(fd);
}

// int wall = -1;

int flood_fill(int pos_x, int pos_y, int target, t_game_map *my_map)
{
	int res = 0;
  
   if(my_map->map_data[pos_x][pos_y] == '1') // if there is no wall or if i haven't been there
      return 0;                                              // already go back
   
   if(my_map->map_data[pos_x][pos_y] == target) // if it's not color go back
      return 1;
   
   my_map->map_data[pos_x][pos_y] = '1'; // mark the point so that I know if I passed through it. 
   
   res += flood_fill(pos_x + 1, pos_y, target, my_map);  // then i can either go south
   res +=flood_fill(pos_x - 1, pos_y, target, my_map);  // or north
   res +=flood_fill(pos_x, pos_y + 1, target, my_map);  // or east
   res +=flood_fill(pos_x, pos_y - 1, target, my_map);  // or west
   
   return res;

}

// int check_paths(t_game_map *my_map)
// {
// 	int cltb;
// 	int exit_count;
// 	char **data;
// 	int x;
// 	int y;

// 	cltb = 0;
// 	exit_count = 0;
// 	data = my_map->map_data;
// 	x = 0;
// 	y = 0;
// 	if (cltb == my_map->max_score && exit_count == 1)
// 		return 1;
// 	if (on_wall)
// 		return 0;
// 	if (on_collectable)
// 		collectables++;
// 	if (on_exit)
// 		exits++;
// 	replace_current_position_with_wall;
// 	if (one_of_the_four_adjacent_directions_is_possible)
// 		return 1;
// 	return 0;
// }

void get_data(char *file, t_game_map *my_map)
{
	int fd;
	// char *temp_str;
	int i;

	fd = open(file, O_RDONLY);
	my_map->map_data = malloc(sizeof(char *) * my_map->map_height);
	i = 0;
	// temp_str = get_next_line(fd);
	my_map->map_data[i] = malloc(sizeof(char) * my_map->map_length);
	my_map->map_data[i] = get_next_line(fd);
	while(my_map->map_data[i] != NULL)
	{
		// set_positions(my_map->map_data[i], my_map, i);
		i++;
		// temp_str = get_next_line(fd);
		my_map->map_data[i] = malloc(sizeof(char) * my_map->map_length);
		my_map->map_data[i] = get_next_line(fd);
	}	
	close(fd);
}

void parse_map(char *file, t_game_map *my_map)
{
	count_size(file, my_map);
	get_data(file, my_map);
	flood_fill(my_map->player_position[0], my_map->player_position[1], 'E', my_map);
}



int main()
{
	t_game_map map;
	valid_map("/Users/asmolnya/Projects/so_long/map2.ber", &map);
	parse_map("/Users/asmolnya/Projects/so_long/map2.ber", &map);
	return 1;
}