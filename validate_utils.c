/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:39:07 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/10 18:54:51 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_lengths(int fd, char **str1)
{
	if (!check_first_line(fd, str1))
		return (0);
	return (check_subsequent_lines(fd, *str1));
}

int	check_str(int fd)
{
	char	*str1;

	if (!check_lengths(fd, &str1))
		return (0);
	return (check_walls_and_cleanup(fd, str1));
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

void	set_ij(int *i, int *j)
{
	*j = 0;
	(*i)++;
}
