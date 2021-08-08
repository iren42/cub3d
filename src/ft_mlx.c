
#include "cub3d.h"
//	 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19
/*
const char map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' ,'1', '1', '1', '1', '1', '1', '0'}, //0
	{'1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, //1
	{'1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, // 2
	{'1', '0', '0', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '1', '0', '0', '1'}, // 3
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, // 4
	{'1', '0', '0', '0', '0', '0', '0', 'N', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'}, // 5
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'}, // 6
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'}, // 7
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '0', '0', '1'}, // 8
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, // 9
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, // 10
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, // 11
	{'0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '0'} // 12
};
*/


// setup player
static void	ft_setup_player(t_data *data)
{
	// rotate player accordingly
	if (data->img.tmap->map[data->img.tmap->player_y][data->img.tmap->player_x] == 'S')
		data->img.player.rotation_angle = PI / 2; // use 'N', 'S', 'E', 'W'
	else if (data->img.tmap->map[data->img.tmap->player_y][data->img.tmap->player_x] == 'N')
		data->img.player.rotation_angle = 3 * PI / 2; // use 'N', 'S', 'E', 'W'
	else if (data->img.tmap->map[data->img.tmap->player_y][data->img.tmap->player_x] == 'W')
		data->img.player.rotation_angle = PI; // use 'N', 'S', 'E', 'W'
	else if (data->img.tmap->map[data->img.tmap->player_y][data->img.tmap->player_x] == 'E')
		data->img.player.rotation_angle = 0; // use 'N', 'S', 'E', 'W'
	data->img.tmap->map[data->img.tmap->player_y][data->img.tmap->player_x] = '0';
	// player's starting position
	data->img.player.x = (TILE_SIZE * (data->img.tmap->player_x + 0.5));
	data->img.player.y = (TILE_SIZE * (data->img.tmap->player_y + 0.5));
//	printf("1 player's starting position = (%d, %d)\n", data->img.tmap->player_x, data->img.tmap->player_y); 
//	printf("2 player's starting position = (%d, %d)\n", data->img.player.x, data->img.player.y);
	data->img.player.width = 5;
	data->img.player.height= 5;
	data->img.player.turn_dir = 0;
	data->img.player.walk_dir = 0;
	data->img.player.cam_dir = 0;
	data->img.player.walk_speed = 10;	// was 50
	data->img.player.turn_speed = 20 * (PI / 180); // was 45
	data->img.rays = malloc(sizeof(t_ray) * data->img.width);
}

int	ft_create_mlx_win_and_img(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (FAILURE);
	mlx_get_screen_size(data->mlx_ptr, &data->img.width, &data->img.height);
//	printf("screen resolution %d %d\n", data->img.width, data->img.height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img.width, data->img.height, "my window");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (FAILURE);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, data->img.width, data->img.height);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	return (SUCCESS);
}

void	ft_free_and_destroy_mlx_win(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->tex[No].mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->tex[So].mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->tex[We].mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->tex[Ea].mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data->img.rays);
	free(data->tex);
}

int ft_mlx(t_map *map)
{
	t_data	data;
	int err;

	(void)err;
	data.img.tmap = map;
	err = ft_create_mlx_win_and_img(&data);
	ft_setup_player(&data);
	ft_import_xpm_file(&data, map);
	ft_refresh_img(&data);
	ft_mlx_hook(&data);
	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	ft_free_and_destroy_mlx_win(&data);
	printf("mlx end**\n");
	return (SUCCESS);
}
