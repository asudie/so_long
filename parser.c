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

 int check_paths(int pos_x, int pos_y, t_game_map *my_map)
 {
	int collectables;

	collectables = 0;
 	if (collectables == my_map->max_score && exit_count == 1)
		return 1;
	if (my_map->map_data[pos_x][pos_y] == '1')
		return 0;
	if (my_map->map_data[pos_x][pos_y] == 'C')
		collectables++;
	if (my_map->map_data[pos_x][pos_y] == 'E')
		exits++;
	my_map->map_data[pos_x][pos_y] = '1';
	if (one_of_the_four_adjacent_directions_is_possible) // here what??
		return map_valid;
	return map_invalid;
 }

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

int check_floods(t_game_map *my_map)
{
	int res;

	res = 0;
	res += flood_fill(my_map->player_position[0], my_map->player_position[1], 'C', my_map);
	res += flood_fill(my_map->player_position[0], my_map->player_position[1], 'E', my_map);
}

int parse_map(char *file, t_game_map *my_map)
{
	count_size(file, my_map);
	get_data(file, my_map);
	if(!check_items(my_map))
	{
      write(2, "Error!\n", 7);   
      return (0);            
   	}
	if(flood_fill(my_map->player_position[0], my_map->player_position[1], 'E', my_map))
		printf("One exit");
	else 
		printf("NOT one exit");
	return 1;
}



int main()
{
	t_game_map map;
	first_check("map2.ber");
	// valid_map("map2.ber", &map); // if this is wrong, don´t continue
	parse_map("map2.ber", &map);
	return 1;
}