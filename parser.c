/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:35:30 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/07 21:49:30 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void floodfill(int pos_x, int pos_y, char **map_check, t_data *data)
{
	if (pos_x < 0 || pos_x >= data->map->map_height || pos_y < 0 || pos_y >= data->map->map_length) // positions change
		return ;
	if(map_check[pos_x][pos_y] == '0' || map_check[pos_x][pos_y] == 'P' || map_check[pos_x][pos_y] == 'C' || map_check[pos_x][pos_y] == 'E')
	{
		map_check[pos_x][pos_y] = 'X';
		if(map_check[pos_x][pos_y] == 'E')
		{
			map_check[pos_x][pos_y] = '1';
			return;
		}
		// print_map(map_check);
			
		floodfill(pos_x + 1, pos_y, map_check, data);
		floodfill(pos_x - 1, pos_y, map_check, data);
		floodfill(pos_x, pos_y + 1, map_check, data);
		floodfill(pos_x, pos_y - 1, map_check, data);
	}
	
}

int	ft_element_count(char **map_check, t_data *data, char element)
{
	int	i;
	int	j;
	int	elements;

	i = 0;
	elements = 0;
	while (i < data->map->map_height)
	{
		j = 0;
		while (j < data->map->map_length)
		{
			if (map_check[i][j] == element)
				elements++;
			j++;
		}
		i++;
	}
	return (elements);
}

int	check_paths(int pos_x, int pos_y, char **map_check, t_data *data)
{
	int	i;

	i = 0;
	floodfill(pos_x, pos_y, map_check, data);
	print_check(map_check, data->map->map_length, data->map->map_height);
	if (ft_element_count(map_check, data, 'E') != 0 || ft_element_count(map_check, data, 'C') != 0)
	{
		// free_map(map_check, data->map->map_height + 1);
		return (0);
	}
	else
	{
		// free_map(map_check, data->map->map_height + 1);
	}
	return (1);
}



// static void	ft_fill(char **map, t_check size, t_check start, char to_fill[])
// {
// 	char	c;
// 	int		i;

// 	if (start.y < 0 || start.y >= size.y || start.x < 0 || start.x >= size.x)
// 		return ;
// 	i = 0;
// 	c = map[start.y][start.x];
// 	while (i < 4)
// 	{
// 		if (c == to_fill[i])
// 		{
// 			map[start.y][start.x] = 'X';
// 			if (to_fill[i] == 'E')
// 				return ;
// 			ft_fill(map, size, (t_check){start.x - 1, start.y}, to_fill);
// 			ft_fill(map, size, (t_check){start.x + 1, start.y}, to_fill);
// 			ft_fill(map, size, (t_check){start.x, start.y - 1}, to_fill);
// 			ft_fill(map, size, (t_check){start.x, start.y + 1}, to_fill);
// 			break ;
// 		}
// 		i++;
// 	}
// }

// static int	ft_check_path(t_game *game, char **map_check)
// {
// 	int	i;

// 	i = 0;
// 	if (ft_element_count(game, map_check, 'E') != 0 \
// 		|| ft_element_count(game, map_check, 'C') != 0)
// 	{
// 		while (map_check[i])
// 		{
// 			free(map_check[i]);
// 			i++;
// 		}
// 		free(map_check);
// 		return (1);
// 	}
// 	else
// 	{
// 		while (map_check[i])
// 		{
// 			free(map_check[i]);
// 			i++;
// 		}
// 		free(map_check);
// 	}
// 	return (0);
// }

void	get_data(char *file, t_data *data)
{
	int	fd;
	int	i;

	fd = open(file, O_RDONLY);
	data->map->map_data = malloc(sizeof(char **) * data->map->map_height);
	if(!data->map->map_data)
	{
		free_map(data->map->map_data, data->map->map_height);
		return;
	}
	i = 0;
	data->map->map_data[i] = get_next_line(fd);
	while (i < data->map->map_height - 1)
	{
		i++;
		data->map->map_data[i] = get_next_line(fd);
	}
	close(fd);
}

void free_map(char **map_check, int size)
{
	int	i;

	i = 0;
	while(i < size)
	{
		free(map_check[i]);
		i++;
	}
	free(map_check);
}

int	parse_map(char *file, t_data *data)
{
	char	**map_check;

	if (count_size(file, data->map))
	{
		get_data(file, data);
		map_check = copy_map(data->map);
		if (!check_items(data->map)) // invalid read
		{
			write(2, "Error\nSometing is wrong with items\n", 36);
			free_map(map_check, data->map->map_height + 1);
			free_map(data->map->map_data, data->map->map_height);
			return (0);
		}
		if (!check_paths(data->map->player_position[0],
				data->map->player_position[1], map_check, data)) // invalid read
		{
			write(2, "Error\nThe map is unsolvable\n", 28);
			free_map(map_check, data->map->map_height + 1);
			free_map(data->map->map_data, data->map->map_height);
			return (0);
		}
		data->map->game_over = 0;
		data->map->game_score = 0;
		free_map(map_check, data->map->map_height + 1);
		return (1);
	}
	return (0);
}
