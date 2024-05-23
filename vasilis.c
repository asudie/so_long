#include <mlx.h>

int main(void)
{
	// t_data *data = malloc(sizeof(t_data));
	// data->map = malloc(sizeof(t_game_map));
	// // t_game_map map;
	// first_check("map1.ber");
	// parse_map("map1.ber", data);
	// // if this is wrong, don´t continue
	// print_map(data);
    void *mlx_ptr = mlx_init();
	// data->mlx_ptr = mlx_init();
	// if (!data->mlx_ptr)
	// 	return (1); // HERE
	void *win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "Help Bibi find the rocket");
	// if (!data->win_ptr)
	// 	return (free(data->mlx_ptr), 1);
	// void *img;
	// /*int x = 1920 / data->map->map_length;
	// int y = 1080 / data->map->map_height;
	// // img = mlx_new_image(data->mlx_ptr, 1920, 1080);

	// data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/background.xpm", &x, &y);
	// data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/wall.xpm", &x, &y);
	// data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/player.xpm", &x, &y);
	// data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/collect.xpm", &x, &y);
	// data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/exit.xpm", &x, &y); */
	// draw_map(data);
	// // mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, 50, 50);

	// // Register key release hook
	// // mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);

	// // Register destroy hook
	// // mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);

	// // Loop over the MLX pointer
	mlx_loop(win_ptr);
	return (0);
}