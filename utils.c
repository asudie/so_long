/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:18:33 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/10 18:51:21 by asmolnya         ###   ########.fr       */
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

int	check_walls_and_cleanup(int fd, char *str1)
{
	char	*str_next;

	str_next = get_next_line(fd);
	while (str_next != NULL)
	{
		if (!check_walls(str_next))
		{
			free_mem(str1, str_next);
			return (0);
		}
		free(str_next);
		str_next = get_next_line(fd);
	}
	free_mem(str1, str_next);
	return (1);
}

int	check_first_line(int fd, char **str1)
{
	*str1 = get_next_line(fd);
	if (!check_one(*str1))
	{
		free(*str1);
		return (0);
	}
	return (1);
}

int	check_subsequent_lines(int fd, char *str1)
{
	char	*str_next;

	str_next = get_next_line(fd);
	while (str_next != NULL)
	{
		if (ft_strlen(str1) != ft_strlen(str_next))
		{
			if (str_next[ft_strlen(str_next) - 1] != '\n')
			{
				if (!check_one(str_next))
				{
					free_mem(str1, str_next);
					return (0);
				}
				free(str_next);
				str_next = get_next_line(fd);
				continue ;
			}
			free_mem(str1, str_next);
			return (0);
		}
		free(str_next);
		str_next = get_next_line(fd);
	}
	return (1);
}
