/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:20:24 by asmolnya          #+#    #+#             */
/*   Updated: 2024/05/31 16:11:41 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	(void)data;
	key_work(keysym, data);
	return (0);
}

void	check_draw(t_data *data, int i, int j, int x)
{
	if (data->map->map_data[i][j] == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[0], j * x, i * x);
	if (data->map->map_data[i][j] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[1], j * x, i * x);
	if (data->map->map_data[i][j] == 'P')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[2], j * x, i * x);
	if (data->map->map_data[i][j] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[3], j * x, i * x);
	if (data->map->map_data[i][j] == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[4], j * x, i * x);
	if (data->map->map_data[i][j] == 'L')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[5], j * x, i * x);
	if (data->map->map_data[i][j] == 'O')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->textures[6], j * x, i * x);
}

void	draw_map(t_data *data)
{
	int	x;
	int	i;
	int	j;

	x = 65;
	load_textures(data, x);
	i = 0;
	while (i < data->map->map_height)
	{
		j = 0;
		while (data->map->map_data[i][j] != '\0'
			&& data->map->map_data[i][j] != '\n')
		{
			check_draw(data, i, j, x);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*data;
	char	*file;

	data = malloc(sizeof(t_data));
	data->map = malloc(sizeof(t_game_map));
	file = argv[1];
	if (first_check(file) && parse_map(file, data))
	{
		data->mlx_ptr = mlx_init();
		if (!data->mlx_ptr)
			return (1);
		data->win_ptr = mlx_new_window(data->mlx_ptr, 65
				* data->map->map_length, 65 * data->map->map_height,
				"Help Bibi find the rocket");
		if (!data->win_ptr)
			return (free(data->mlx_ptr), 1);
		draw_map(data);
		mlx_key_hook(data->win_ptr, on_keypress, data);
		mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, on_destroy,
			data);
		mlx_loop(data->mlx_ptr);
	}
	free(data->map);
	free(data);
	return (0);
}
