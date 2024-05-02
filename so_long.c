#include "so_long.h"


// int check_map() // recursive
// {
// 	if (all_collectables_collected && exit_count == 1)
// 		return map_valid;
// 	if (on_wall)
// 		return map_invalid;
// 	if (on_collectable)
// 		collectables++;
// 	if (on_exit)
// 		exits++;
// 	replace_current_position_with_wall;
// 	if (one_of_the_four_adjacent_directions_is_possible)
// 		return map_valid;
// 	return map_invalid;
// }

// typedef struct s_data
// {
// 	void *mlx_ptr;
// 	void *win_ptr;
// } t_data;
 
// int on_destroy(t_data *data)
// {
// 	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 	mlx_destroy_display(data->mlx_ptr);
// 	free(data->mlx_ptr);
// 	exit(0);
// 	return (0);
// }
 
// int on_keypress(int keysym, t_data *data)
// {
// 	(void)data;
// 	printf("Pressed key: %d\\n", keysym);
// 	return (0);
// }

// char **parse_map(int fd)
// {
// 	valid_map(fd);
// }


 
// int main(void)
// {

	// t_data data;
 
	// data.mlx_ptr = mlx_init();
	// if (!data.mlx_ptr)
	// 	return (1);
	// data.win_ptr = mlx_new_window(data.mlx_ptr, 600, 400, "hi :)");
	// if (!data.win_ptr)
	// 	return (free(data.mlx_ptr), 1);
 
	// // Register key release hook
	// mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);
 
	// // Register destroy hook
	// mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
 
	// // Loop over the MLX pointer
	// mlx_loop(data.mlx_ptr);
// 	return (0);
// }

// int main()
// {
// 	int fd;
// 	// t_game_map my_map;
// 	fd = open("/Users/asmolnya/Projects/so_long/map2.ber",O_RDONLY);
// 	if(fd == -1)
//    {
//       write(2, "Error!\n", 7);   
//       return (0);            
//    }
//    if(check_str(fd))
// 		printf("Map is ok\n");
// 	else
// 		printf("Map is NOT ok\n");
// 	// char *str1 = "1111111";
// 	char *str1 = "111011";
// 	if(check_one(str1))
// 		printf("Only 1 in str\n");
// 	else
// 		printf("NOT only 1 in str\n");
//     // my_map.map_data = parse_map(fd);
// 	return (0);
// }