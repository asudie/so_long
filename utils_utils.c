/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmolnya <asmolnya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:52:30 by asmolnya          #+#    #+#             */
/*   Updated: 2024/06/10 18:54:55 by asmolnya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ber(char *str)
{
	if (ft_strncmp((str + ft_strlen(str) - 4), ".ber", 4))
		return (0);
	return (1);
}

void	free_mem(char *str1, char *str_next)
{
	free(str1);
	free(str_next);
}
