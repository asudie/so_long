#include "so_long.h"

int check_one(char *str)
{
	int i = 0;
	if(str)
	{
		while(str[i] != '\0')
		{
			if(str[i] != '1' && str[i] != '\n')
				return 0;
			i++;
		}
		return 1;
	}
	return (0);
}

int nl_strlen(char *s)
{
	int	size;

	size = 0;
	while (s[size] != '\n')
	{
		size++;
	}
	return (size);
}

int check_walls(char *str)
{
	if(str[0] != '1' || str[nl_strlen(str) - 1] != '1')
		return 0;
	return 1;
}

int check_str(int fd)
{
	char *str1 = get_next_line(fd);
	if(!check_one(str1))
		return 0;
	char *str_next = get_next_line(fd);
	while(str_next != NULL)
	{
		if(ft_strlen(str1) != ft_strlen(str_next))
		{
			if(str_next[ft_strlen(str_next) - 1] != '\n')
			{
				if(!check_one(str_next))
					return 0;
				str_next = get_next_line(fd);
				continue;
			}
			return (0);
		}
		if(!check_walls(str_next))
			return 0;
		str_next = get_next_line(fd);
	}
	return (1);
}

int check_items(t_game_map *my_map)
{
	// char *str;
	int c;
	int pe;
	int i;
	int j;
	
	// str = get_next_line(fd);
	i = 0;
	j = 0;
	c = 0;
	pe = 0;
	while(my_map->map_data[i][j] != '\0')
	{
		while(my_map->map_data[i][j] != '\n' && my_map->map_data[i][j] != '\0')
		{
			if(my_map->map_data[i][j] == 'E')
				pe++;
			else if(my_map->map_data[i][j] == 'P')
			{
				my_map->player_position[0] = i;
				my_map->player_position[1] = j;
				pe++;
			}
			else if(my_map->map_data[i][j] == 'C')
			{
				c++;
			} else if(my_map->map_data[i][j] != '0' && my_map->map_data[i][j] != '\0' && my_map->map_data[i][j] != '\n' && my_map->map_data[i][j] != '1')
			{
				return (0);
			}
				
			j++;
		}
		if(my_map->map_data[i][j] != '\0')
		{
			j = 0;
			i++;
		}
	}
	if(pe == 2 && c >= 1)
	{
		my_map->max_score = c;
		return (1);
	}	
	return (0);
}

int check_ber(char *str)
{
	if(ft_strncmp((str + ft_strlen(str) - 4), ".ber", 4))
		return 0;
	return 1;
}

int first_check(char *str)
{
	int fd;
	fd = open(str, O_RDONLY);
	if(fd == -1)
   {
      write(2, "Error\n", 6);   
      return (0);            
   }
	if(!check_ber(str) || !check_str(fd))
	{
      write(2, "Error\n", 6);   
      return (0);            
	}
	close(fd);
	return 1;
}
