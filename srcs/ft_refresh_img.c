#include "cub3d.h"

void	ft_refresh_img(t_data *data)
{	
	ft_move_player(data);
	if (data->img.mlx_img != NULL)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = NULL;
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);

	ft_render_map(&data->img);
	ft_render_player(&data->img, *data->img.player);
	if (data->img.mlx_img != NULL)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}
