
#include "cub3d.h"
//	 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19
const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1}, //0
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, //1
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 2
	{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1}, // 3
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 4
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, // 5
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, // 6
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1}, // 7
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1}, // 8
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 9
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 10
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // 11
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1} // 12
};



int	ft_map_has_wall_at(float x, float y)
{
	int map_grid_index_x;
	int map_grid_index_y;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) // out of boundary
		return (1);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
//	printf("index x = %d\t y = %d\t %d\n", map_grid_index_x, map_grid_index_y, 
//		map[map_grid_index_y][map_grid_index_x]);
	return (map[map_grid_index_y][map_grid_index_x] != 0);
}
void	ft_update_player_s_values(t_data *data)
{
	float	move_step;
	float	new_player_x;
	float	new_player_y;
	t_player	*p;

	p = data->img.player;
	p->rotation_angle += p->turn_dir * p->turn_speed;
	move_step = p->walk_dir * p->walk_speed;
	new_player_x = p->x + cos(p->rotation_angle) * move_step;
	new_player_y = p->y + sin(p->rotation_angle) * move_step;
	if (!ft_map_has_wall_at(new_player_x, new_player_y))
	{
		p->x = new_player_x;
		p->y = new_player_y;
	}
}


// Start position of the player
void	ft_setup_player(t_img *img)
{
	t_player	*new_player; // TODO: free it

	new_player = malloc(sizeof(new_player));
	if (new_player != NULL)
	{
		new_player->x = WINDOW_WIDTH / 2;
		new_player->y = WINDOW_HEIGHT / 2;
		new_player->width = 5;
		new_player->height= 5;
		new_player->turn_dir = 0;
		new_player->walk_dir = 0;
		new_player->rotation_angle = PI / 2;
		new_player->walk_speed = 10;	// was 50
		new_player->turn_speed = 20 * (PI / 180); // was 45
		img->player = new_player;
	}
}
int	ft_create_mlx_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (FAILURE);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (FAILURE);
	}
	data->img.mlx_img = NULL;
	return (SUCCESS);
}


int ft_mlx(t_map map)
{
	t_data	data;
	int err;

	ft_setup_player(&data.img);
	err = ft_create_mlx_window(&data);
	ft_refresh_img(&data);
	ft_mlx_hook(&data);
	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	printf("mlx end**\n");
	return (SUCCESS);
}
