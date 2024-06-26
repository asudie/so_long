/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:53:32 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/08 13:46:02 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	count_size(char *file, t_game_map *my_map)
{
	int		fd;
	char	*temp_str;
	int		i;
	int		res;

	init_values(&i, &res);
	fd = open(file, O_RDONLY);
	temp_str = get_next_line(fd);
	if (temp_str)
	{
		res = 1;
		my_map->map_length = nl_strlen(temp_str);
		while (temp_str != NULL)
		{
			i++;
			free(temp_str);
			temp_str = get_next_line(fd);
		}
		my_map->map_height = i;
	}
	free(temp_str);
	close(fd);
	if (my_map->map_height > 31 || my_map->map_length > 40)
		write(2, "Error\nMap is too big!\n", 22);
	return (res);
}

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

char	**copy_map(t_game_map *my_map)
{
	char	**map_check;
	int		i;

	i = 0;
	map_check = malloc((sizeof(char *) * (my_map->map_height + 1)));
	if (!map_check)
		return (NULL);
	while (i < my_map->map_height)
	{
		map_check[i] = ft_strcpy(map_check[i], my_map->map_data[i]);
		i++;
	}
	map_check[i] = NULL;
	return (map_check);
}

int	mesg_and_free(char *message, char **map_check, t_data *data)
{
	write(2, message, ft_strlen(message));
	free_map(map_check, data->map->map_height + 1);
	free_map(data->map->map_data, data->map->map_height);
	return (0);
}

void	free_map(char **map_check, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(map_check[i]);
		i++;
	}
	free(map_check);
}
