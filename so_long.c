#include "so_long.h"

int on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	exit(0);
	return (0);
}

void left_work(t_data *data)
{
	int x = data->map->player_position[0];
	int y = data->map->player_position[1];
	if(data->map->map_data[x - 1][y] != '1' && data->map->map_data[x - 1][y] != 'E')
	{
		if(data->map->map_data[x - 1][y] == 'C')
			data->map->game_over++;
		data->map->map_data[x - 1][y] = 'P';
		data->map->map_data[x][y] = '0';
		data->map->player_position[0] = x - 1;
		data->map->game_score++;
	}
}

void down_work(t_data *data)
{
	int x = data->map->player_position[0];
	int y = data->map->player_position[1];
	if(data->map->map_data[x][y - 1] != '1' && data->map->map_data[x][y - 1] != 'E')
	{
		if(data->map->map_data[x][y - 1] == 'C')
			data->map->game_over++;
		data->map->map_data[x][y - 1] = 'P';
		data->map->map_data[x][y] = '0';
		data->map->player_position[1] = y - 1;
		data->map->game_score++;
	}
}

void up_work(t_data *data)
{
	int x = data->map->player_position[0];
	int y = data->map->player_position[1];
	if(data->map->map_data[x][y + 1] != '1'  && data->map->map_data[x][y + 1] != 'E')
	{
		if(data->map->map_data[x][y + 1] == 'C')
			data->map->game_over++;
		data->map->map_data[x][y + 1] = 'P';
		data->map->map_data[x][y] = '0';
		data->map->player_position[1] = y + 1;
		data->map->game_score++;
	}
}

void right_work(t_data *data)
{
	int x = data->map->player_position[0];
	int y = data->map->player_position[1];
	if(data->map->map_data[x + 1][y] != '1' && data->map->map_data[x + 1][y] != 'E')
	{
		if(data->map->map_data[x + 1][y] == 'C')
			data->map->game_over++;
		data->map->map_data[x + 1][y] = 'P';
		data->map->map_data[x][y] = '0';
		data->map->player_position[0] = x + 1;
		data->map->game_score++;
	}
}

void key_work(int keysym, t_data *data)
{
	if(keysym == 97 || keysym == 65361)
		left_work(data);
	if(keysym == 115 || keysym == 65364)
		down_work(data);
	if(keysym == 119 || keysym == 65362)
		up_work(data);
	if(keysym == 100 || keysym == 65363)
		right_work(data);
	draw_map(data);
}

int on_keypress(int keysym, t_data *data)
{
	(void)data;
	printf("Pressed key: %d\n", keysym);
	key_work(keysym, data);
	return (0);
}

void draw_map(t_data *data)
{
	int x = 65;
	int y = 65;
	int i;
	int j;

	// FIXME : make this a separate func

	data->textures[0] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/background.xpm", &x, &y);
	data->textures[1] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/wall.xpm", &x, &y);
	data->textures[2] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/player.xpm", &x, &y);
	data->textures[3] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/collect.xpm", &x, &y);
	data->textures[4] = mlx_xpm_file_to_image(data->mlx_ptr, "textures/exit.xpm", &x, &y);

	i = 0;
	while (i < data->map->map_height) // Check for the end of the map array
	{
		j = 0;
		while (data->map->map_data[i][j] != '\0' && data->map->map_data[i][j] != '\n') // Check for end of line or end of string
		{
			if (data->map->map_data[i][j] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[0], j * x, i * y);
			if (data->map->map_data[i][j] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[1], j * x, i * y);
			if (data->map->map_data[i][j] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[2], j * x, i * y);
			if (data->map->map_data[i][j] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[3], j * x, i * y);
			if (data->map->map_data[i][j] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->textures[4], j * x, i * y);
			j++;
		}
		i++;
	}
}

void print_map(t_data *data)
{
	int i, j;
	i = 0;
	// printf("", data->map_height);
	while (i < data->map->map_height) // Loop through all rows
	{
		j = 0;
		while(j < data->map->map_length)
		{
			write(1, &data->map->map_data[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_data *data = malloc(sizeof(t_data));
	data->map = malloc(sizeof(t_game_map));
	char *file = argv[1];
	first_check(file);
	parse_map(file, data);
	// if this is wrong, don´t continue
	// print_map(data);

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1); // HERE
	data->win_ptr = mlx_new_window(data->mlx_ptr, 65 * data->map->map_length, 65 * data->map->map_height, "Help Bibi find the rocket");
	if (!data->win_ptr)
		return (free(data->mlx_ptr), 1);
	
	draw_map(data);

	// Register key release hook
	// mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &data);

	mlx_key_hook(data->win_ptr, on_keypress, data);

	// Register destroy hook
	mlx_hook(data->win_ptr, DestroyNotify, StructureNotifyMask, on_destroy, data);

	// Loop over the MLX pointer
	mlx_loop(data->mlx_ptr);
	return (0);
}
