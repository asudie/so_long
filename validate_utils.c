/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:39:07 by asmolnya          #+#    #+#             */
/*   Updated: 2024/05/31 11:40:39 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ber(char *str)
{
	if (ft_strncmp((str + ft_strlen(str) - 4), ".ber", 4))
		return (0);
	return (1);
}

int	check_str(int fd)
{
	char	*str1;
	char	*str_next;

	str1 = get_next_line(fd);
	if (!check_one(str1))
		return (0);
	str_next = get_next_line(fd);
	while (str_next != NULL)
	{
		if (ft_strlen(str1) != ft_strlen(str_next))
		{
			if (str_next[ft_strlen(str_next) - 1] != '\n')
			{
				if (!check_one(str_next))
					return (0);
				str_next = get_next_line(fd);
				continue ;
			}
			return (0);
		}
		if (!check_walls(str_next))
			return (0);
		str_next = get_next_line(fd);
	}
	return (1);
}

int	nl_strlen(char *s)
{
	int	size;

	size = 0;
	while (s[size] != '\n')
	{
		size++;
	}
	return (size);
}

int	check_walls(char *str)
{
	if (str[0] != '1' || str[nl_strlen(str) - 1] != '1')
		return (0);
	return (1);
}
