/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:18:33 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/10 13:56:51 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	data_start(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 65 * data->map->map_length, 65
			* data->map->map_height, "Help Bibi find the rocket");
	draw_map(data);
	mlx_key_hook(data->win_ptr, on_keypress, data);
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, on_destroy,
		data);
	mlx_loop(data->mlx_ptr);
}

int	data_init(t_data **data)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (0);
	(*data)->map = malloc(sizeof(t_game_map));
	if (!(*data)->map)
		return (0);
	(*data)->map->collectables = 0;
	(*data)->map->exits = 0;
	return (1);
}
