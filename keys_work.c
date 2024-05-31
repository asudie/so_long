/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_work.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:25:58 by asmolnya          #+#    #+#             */
/*   Updated: 2024/05/31 12:29:53 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	up_work(t_data *data)
{
	int	x;
	int	y;

	x = data->map->player_position[0];
	y = data->map->player_position[1];
	if (data->map->map_data[x - 1][y] == 'O')
	{
		if (data->map->game_over == data->map->max_score)
			on_destroy(data);
	}
	if (data->map->map_data[x - 1][y] != '1' && data->map->map_data[x
		- 1][y] != 'E')
	{
		if (data->map->map_data[x - 1][y] == 'C')
		{
			data->map->game_over++;
			if (data->map->game_over == data->map->max_score)
				find_exit(data);
		}
		data->map->map_data[x - 1][y] = 'P';
		data->map->map_data[x][y] = '0';
		data->map->player_position[0] = x - 1;
		data->map->game_score++;
		ft_printf("Number of movements: %d\n", data->map->game_score);
	}
}

void	left_work(t_data *data)
{
	int	x;
	int	y;

	x = data->map->player_position[0];
	y = data->map->player_position[1];
	if (data->map->map_data[x][y - 1] == 'O')
	{
		if (data->map->game_over == data->map->max_score)
			on_destroy(data);
	}
	if (data->map->map_data[x][y - 1] != '1' && data->map->map_data[x][y
		- 1] != 'E')
	{
		if (data->map->map_data[x][y - 1] == 'C')
		{
			data->map->game_over++;
			if (data->map->game_over == data->map->max_score)
				find_exit(data);
		}
		data->map->map_data[x][y - 1] = 'L';
		data->map->map_data[x][y] = '0';
		data->map->player_position[1] = y - 1;
		data->map->game_score++;
		ft_printf("Number of movements: %d\n", data->map->game_score);
	}
}

void	right_work(t_data *data)
{
	int	x;
	int	y;

	x = data->map->player_position[0];
	y = data->map->player_position[1];
	if (data->map->map_data[x][y + 1] == 'O')
	{
		if (data->map->game_over == data->map->max_score)
			on_destroy(data);
	}
	if (data->map->map_data[x][y + 1] != '1' && data->map->map_data[x][y
		+ 1] != 'E')
	{
		if (data->map->map_data[x][y + 1] == 'C')
		{
			data->map->game_over++;
			if (data->map->game_over == data->map->max_score)
				find_exit(data);
		}
		data->map->map_data[x][y + 1] = 'P';
		data->map->map_data[x][y] = '0';
		data->map->player_position[1] = y + 1;
		data->map->game_score++;
		ft_printf("Number of movements: %d\n", data->map->game_score);
	}
}

void	down_work(t_data *data)
{
	int	x;
	int	y;

	x = data->map->player_position[0];
	y = data->map->player_position[1];
	if (data->map->map_data[x + 1][y] == 'O')
	{
		if (data->map->game_over == data->map->max_score)
			on_destroy(data);
	}
	if (data->map->map_data[x + 1][y] != '1' && data->map->map_data[x
		+ 1][y] != 'E')
	{
		if (data->map->map_data[x + 1][y] == 'C')
		{
			data->map->game_over++;
			if (data->map->game_over == data->map->max_score)
				find_exit(data);
		}
		data->map->map_data[x + 1][y] = 'P';
		data->map->map_data[x][y] = '0';
		data->map->player_position[0] = x + 1;
		data->map->game_score++;
		ft_printf("Number of movements: %d\n", data->map->game_score);
	}
}

void	key_work(int keysym, t_data *data)
{
	if (keysym == 97 || keysym == 65361)
		left_work(data);
	if (keysym == 115 || keysym == 65364)
		down_work(data);
	if (keysym == 119 || keysym == 65362)
		up_work(data);
	if (keysym == 100 || keysym == 65363)
		right_work(data);
	if (keysym == 65307)
		on_destroy(data);
	draw_map(data);
}
