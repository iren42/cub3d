
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



// Start position of the player
void	ft_setup_player(t_img *img)
{
	/*	t_player	*new_player; // TODO: free it

		new_player = malloc(sizeof(t_player));
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
	 */
	img->player.x = WINDOW_WIDTH / 2;
	img->player.y = WINDOW_HEIGHT / 2;
	img->player.width = 5;
	img->player.height= 5;
	img->player.turn_dir = 0;
	img->player.walk_dir = 0;
	img->player.rotation_angle = PI / 2;
	img->player.walk_speed = 10;	// was 50
	img->player.turn_speed = 20 * (PI / 180); // was 45
	printf("img %d %d\n", img->player.x, img->player.turn_dir);
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

	(void)err;
	(void)map;
	ft_setup_player(&data.img);
	err = ft_create_mlx_window(&data);
	ft_refresh_img(&data);
	ft_mlx_hook(&data);
	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	//	free(data.img.player);
	printf("mlx end**\n");
	return (SUCCESS);
}
