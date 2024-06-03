/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:35:30 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/03 16:50:45 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_paths(int pos_x, int pos_y, char **map_check, t_data *data)
{
	if (data->map->collectables == data->map->max_score
		&& data->map->exits == 1)
		return (1);
	if (map_check[pos_x][pos_y] == '1')
		return (0);
	if (map_check[pos_x][pos_y] == 'C')
		data->map->collectables++;
	if (map_check[pos_x][pos_y] == 'E')
		data->map->exits++;
	map_check[pos_x][pos_y] = '1';
	if (check_paths(pos_x + 1, pos_y, map_check, data) || check_paths(pos_x
			- 1, pos_y, map_check, data) || check_paths(pos_x, pos_y + 1,
			map_check, data) || check_paths(pos_x, pos_y - 1, map_check,
			data))
		return (1);
	return (0);
}

void	get_data(char *file, t_data *data)
{
	int	fd;
	int	i;

	fd = open(file, O_RDONLY);
	data->map->map_data = malloc(sizeof(char **) * data->map->map_height);
	i = 0;
	data->map->map_data[i] = get_next_line(fd);
	while (i < data->map->map_height - 1)
	{
		i++;
		data->map->map_data[i] = get_next_line(fd);
	}
	close(fd);
}

void free_map(char **map_check)
{
	int	i;

	i = 0;
	while(map_check[i])
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
		if (!check_items(data->map))
		{
			write(2, "Error\n", 6);
			free_map(map_check);
			return (0);
		}
		if (!check_paths(data->map->player_position[0],
				data->map->player_position[1], map_check, data))
		{
			write(2, "Error\n", 6);
			free_map(map_check);
			return (0);
		}
		data->map->game_over = 0;
		data->map->game_score = 0;
		free_map(map_check);
		return (1);
	}
	return (0);
}
