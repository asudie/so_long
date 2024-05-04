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

// int flood_fill(int pos_x, int pos_y, int target, t_game_map *my_map)
// {
// 	int res = 0;
  
//    if(my_map->map_data[pos_x][pos_y] == '1') // if there is no wall or if i haven't been there
//       return 0;                                              // already go back
   
//    if(my_map->map_data[pos_x][pos_y] == target) // if it's not color go back
//       return 1;
   
//    my_map->map_data[pos_x][pos_y] = '1'; // mark the point so that I know if I passed through it. 
   
//    res += flood_fill(pos_x + 1, pos_y, target, my_map); // then i can either go south
//    res +=flood_fill(pos_x - 1, pos_y, target, my_map);  // or north
//    res +=flood_fill(pos_x, pos_y + 1, target, my_map);  // or east
//    res +=flood_fill(pos_x, pos_y - 1, target, my_map);  // or west
   
//    return res;

// }

int collectables = 0;
int exits = 0;

	// collectables = 0;
	// exits = 0;

 int check_paths(int pos_x, int pos_y, t_game_map *my_map)
 {
 	if (collectables == my_map->max_score && exits == 1)
		return 1;
	if (my_map->map_data[pos_x][pos_y] == '1')
		return 0;
	if (my_map->map_data[pos_x][pos_y] == 'C')
		collectables++;
	if (my_map->map_data[pos_x][pos_y] == 'E')
		exits++;
	my_map->map_data[pos_x][pos_y] = '1';
	if (check_paths(pos_x + 1, pos_y, my_map) || check_paths(pos_x - 1, pos_y, my_map) || check_paths(pos_x, pos_y + 1, my_map) || check_paths(pos_x, pos_y - 1, my_map)) // here what??
		return 1;
	return 0;
 }

void get_data(char *file, t_game_map *my_map)
{
	int fd;
	int i;

	fd = open(file, O_RDONLY);
	my_map->map_data = malloc(sizeof(char *) * my_map->map_height);
	i = 0;
	my_map->map_data[i] = malloc(sizeof(char) * my_map->map_length);
	my_map->map_data[i] = get_next_line(fd);
	while(my_map->map_data[i] != NULL)
	{
		i++;
		my_map->map_data[i] = malloc(sizeof(char) * my_map->map_length);
		my_map->map_data[i] = get_next_line(fd);
	}	
	close(fd);
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
	if(check_paths(my_map->player_position[0], my_map->player_position[1], my_map))
		printf("Map is VALID");
	else 
		printf("Map is INVALID");
	return 1;
}

// int main()
// {
// 	t_game_map map;
// 	first_check("map3.ber");
// 	parse_map("map3.ber", &map);
// 	// if this is wrong, don´t continue
// 	return 1;
// }