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
	while (temp_str != NULL)
	{
		i++;
		temp_str = get_next_line(fd);
	}
	my_map->map_height = i;
	close(fd);
}

int collectables = 0;
int exits = 0;

char	*ft_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	dst = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dst)
		return (NULL);
	while (src[i] != '\0' && src[i] != '\n')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char **copy_map(t_game_map *my_map)
{
	char	**map_check;
	int i = 0;

	map_check = malloc((sizeof(char*) * my_map->map_height));
	while (i < my_map->map_height)
	{
		map_check[i] = ft_strcpy(map_check[i], my_map->map_data[i]);
		i++;
	}
	map_check[i] = NULL;
	return map_check;
}

int check_paths(int pos_x, int pos_y, char	**map_check, int max_score)
{
	

	if (collectables == max_score && exits == 1)
		return 1;
	if (map_check[pos_x][pos_y] == '1')
		return 0;
	if (map_check[pos_x][pos_y] == 'C')
		collectables++;
	if (map_check[pos_x][pos_y] == 'E')
		exits++;
	map_check[pos_x][pos_y] = '1';
	if (check_paths(pos_x + 1, pos_y, map_check, max_score) || check_paths(pos_x - 1, pos_y, map_check, max_score) || check_paths(pos_x, pos_y + 1, map_check, max_score) || check_paths(pos_x, pos_y - 1, map_check, max_score))
		return 1;
	return 0;
}

void get_data(char *file, t_data *data)
{
	int fd;
	int i;

	fd = open(file, O_RDONLY);
	data->map->map_data = malloc(sizeof(char **) * data->map->map_height);
	i = 0;
	// data->map->map_data[i] = malloc(sizeof(char*) * data->map->map_length);
	data->map->map_data[i] = get_next_line(fd);
	printf("%s\n", data->map->map_data[i]);
	while (i < data->map->map_height - 1)
	{
		i++;
		// data->map->map_data[i] = malloc(sizeof(char) * data->map->map_length);
		data->map->map_data[i] = get_next_line(fd);
		printf("%s\n", data->map->map_data[i]);
	}
	print_map(data);
	close(fd);
}

int parse_map(char *file, t_data *data)
{
	count_size(file, data->map);
	get_data(file, data);
	char	**map_check = copy_map(data->map);
	if (!check_items(data->map))
	{
		write(2, "Error!\n", 7);
		return (0);
	}
	if (!check_paths(data->map->player_position[0], data->map->player_position[1], map_check, data->map->max_score))
	{
		write(2, "Error!\n", 7);
		return (0);
	}
	data->map->game_over = 0;
	data->map->game_score = 0;
	return 1;
}
