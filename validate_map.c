/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:35:02 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/08 13:23:37 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_one(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (str[i] != '1' && str[i] != '\n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	change_pos(t_game_map *my_map, int i, int j, int *pe)
{
	my_map->player_position[0] = i;
	my_map->player_position[1] = j;
	(*pe)++;
}

int	loop_func(t_game_map *my_map, int *c, int *pe, int j)
{
	int	i;

	i = 0;
	while (my_map->map_data[i][j] != '\0')
	{
		while (my_map->map_data[i][j] != '\n' && my_map->map_data[i][j] != '\0')
		{
			if (my_map->map_data[i][j] == 'E')
				(*pe)++;
			else if (my_map->map_data[i][j] == 'P')
				change_pos(my_map, i, j, pe);
			else if (my_map->map_data[i][j] == 'C')
				(*c)++;
			else if (my_map->map_data[i][j] != '0'
				&& my_map->map_data[i][j] != '\0'
				&& my_map->map_data[i][j] != '\n'
				&& my_map->map_data[i][j] != '1')
				return (0);
			j++;
		}
		if (my_map->map_data[i][j] != '\0')
			set_ij(&i, &j);
	}
	return (1);
}

int	check_items(t_game_map *my_map)
{
	int	c;
	int	pe;

	if (my_map->map_data[my_map->map_height - 1][my_map->map_length] == '\0')
	{
		c = 0;
		pe = 0;
		if (!loop_func(my_map, &c, &pe, 0))
			return (0);
		if (pe == 2 && c >= 1)
		{
			my_map->max_score = c;
			return (1);
		}
	}
	return (0);
}

int	first_check(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nCan't opem the file\n", 26);
		return (0);
	}
	if (!check_ber(str) || !check_str(fd))
	{
		write(2, "Error\nFile is not .ber or map is not ractangle\n", 47);
		return (0);
	}
	close(fd);
	return (1);
}
