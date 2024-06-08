/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:22:24 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/08 13:46:10 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->map_height)
	{
		j = 0;
		while (j < data->map->map_length)
		{
			write(1, &data->map->map_data[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	print_check(char **map_data, int map_length, int map_height)
{
	int	i;
	int	j;

	i = 0;
	while (i < map_height)
	{
		j = 0;
		while (j < map_length)
		{
			write(1, &map_data[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	load_textures(t_data *data, int x)
{
	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/background.xpm", &x, &x);
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/wall.xpm", &x, &x);
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/player.xpm", &x, &x);
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/collect.xpm", &x, &x);
	data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/exit.xpm", &x, &x);
	data->textures[5] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/player_left.xpm", &x, &x);
	data->textures[6] = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/o_exit.xpm", &x, &x);
}

void	find_exit(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->map_height)
	{
		j = 0;
		while (data->map->map_data[i][j] != '\0'
			&& data->map->map_data[i][j] != '\n')
		{
			if (data->map->map_data[i][j] == 'E')
			{
				data->map->map_data[i][j] = 'O';
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_values(int *i, int *res)
{
	*i = 0;
	*res = 0;
}
