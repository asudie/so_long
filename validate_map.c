#include "so_long.h"

int check_one(char *str)
{
	int i = 0;
	while(str[i] != '\0')
	{
		if(str[i] != '1' && str[i] != '\n')
			return 0;
		i++;
	}
	return 1;
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

int check_items(int fd, t_game_map *map)
{
	char *str;
	int c;
	int p;
	int e;
	int i;
	
	str = get_next_line(fd);
	i = 0;
	c = 0;
	p = 0;
	e = 0;
	while(str != NULL)
	{
		while(str[i] != '\n' && str[i] != '\0')
		{
			if(str[i] == 'E')
				e++;
			else if(str[i] == 'P')
				p++;
			else if(str[i] == 'C')
				c++;
			i++;
		}
		str = get_next_line(fd);
		i = 0;
	}
	if(e == 1 && p == 1 && c >= 1)
	{
		map->max_score = c;
		return (1);
	}	
	return (0);
}

int check_ber(char *str)
{
	int i;

	i = 0;
	if(ft_strncmp((str + ft_strlen(str) - 4), ".ber", 4))
		return 0;
	return 1;
}

int valid_map(char *str, t_game_map *map)
{
	int fd;
	fd = open(str, O_RDONLY);
	if(fd == -1)
   {
      write(2, "Error!\n", 7);   
      return (0);            
   }
	if(!check_ber(str) || !check_str(fd))
	{
      write(2, "Error!\n", 7);   
      return (0);            
	}
	close(fd);
	fd = open(str, O_RDONLY);
	if(!check_items(fd, map))
	{
      write(2, "Error!\n", 7);   
      return (0);            
	}
	close(fd);
	return 1;
}

// int main()
// {
//    if(valid_map("/Users/asmolnya/Projects/so_long/map2.ber"))
// 		printf("Map is ok\n");
// 	else
// 		printf("Map is NOT ok\n");
// 	// if (check_ber("/Users/asmolnya/Projects/so_long/map2.ber"))
// 	// 	printf("It's BER\n");
// 	// else
// 	// 	printf("It's NOT BER\n");
// 	// char *str1 = "1111111";
// 	// char *str1 = "111011";
// 	// if(check_one(str1))
// 	// 	printf("Only 1 in str\n");
// 	// else
// 	// 	printf("NOT only 1 in str\n");
//     // my_map.map_data = parse_map(fd);
// 	return (0);
// }