
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
void	ft_setup_img(t_img *img)
{
	img->player.x = WINDOW_WIDTH / 2;
	img->player.y = WINDOW_HEIGHT / 2;
	img->player.width = 5;
	img->player.height= 5;
	img->player.turn_dir = 0;
	img->player.walk_dir = 0;
	img->player.rotation_angle = PI / 2;
	img->player.walk_speed = 10;	// was 50
	img->player.turn_speed = 20 * (PI / 180); // was 45
	//	printf("img %d %d\n", img->player.x, img->player.turn_dir);
	img->rays = malloc(sizeof(t_ray) * NUM_RAYS);
}

int	ft_create_mlx_win_and_img(t_data *data)
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
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	return (SUCCESS);
}

void	ft_free_and_destroy_mlx_win(t_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_image(data->mlx_ptr, data->tex[No].tex_img);
	mlx_destroy_image(data->mlx_ptr, data->tex[So].tex_img);
	mlx_destroy_image(data->mlx_ptr, data->tex[We].tex_img);
	mlx_destroy_image(data->mlx_ptr, data->tex[Ea].tex_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free(data->img.rays);
	free(data->tex);
}

int ft_mlx(t_map map)
{
	t_data	data;
	int err;

	(void)err;
	(void)map;
	ft_setup_img(&data.img);
	err = ft_create_mlx_win_and_img(&data);
	ft_import_xpm_file(&data, map);
	ft_refresh_img(&data);
	ft_mlx_hook(&data);
	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	ft_free_and_destroy_mlx_win(&data);
	printf("mlx end**\n");
	return (SUCCESS);
}
