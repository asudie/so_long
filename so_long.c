#include "so_long.h"

/* int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

int on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\\n", keysym);
	return (0);
} */

int main(void)
{
	t_data *data = malloc(sizeof(t_data));
	data->map = malloc(sizeof(t_game_map));
	// t_game_map map;
	first_check("map1.ber");
	parse_map("map1.ber", data->map);
	// if this is wrong, don´t continue

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1); // HERE
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1920, 1080, "Help Bibi find the rocket");
	if (!data->win_ptr)
		return (free(data->mlx_ptr), 1);
	void *img;
	int x = 1920 / data->map->map_length;
	int y = 1080 / data->map->map_height;
	// img = mlx_new_image(data->mlx_ptr, 1920, 1080);

	img = mlx_xpm_file_to_image(data->mlx_ptr, "textures/player.xpm", &x, &y);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img, 50, 50);

	// Register key release hook
	// mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);

	// Register destroy hook
	// mlx_hook(data.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &data);

	// Loop over the MLX pointer
	mlx_loop(data->mlx_ptr);
	return (0);
}
