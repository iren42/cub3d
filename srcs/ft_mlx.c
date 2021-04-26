#include <X11/X.h>
#include <X11/keysym.h>
#include "cub3d.h"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define MLX_ERROR 1

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF



/* The x and y coordinates of the rect corresponds to its upper left corner. */

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height && i <= WINDOW_HEIGHT)
	{
		j = rect.x;
		while (j < rect.x + rect.width && j <= WINDOW_WIDTH)
			ft_img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			ft_img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

void	ft_move(t_rect *r)
{
	int move = 1;
	if (r->x + move < WINDOW_WIDTH - r->width)
		r->x += move;
	if (r->y + move < WINDOW_HEIGHT - r->height)
		r->y += move;
}


int	render(t_data *data)
{

	ft_move(data->img.rect);
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, WHITE_PIXEL);
	render_rect(&data->img, *(data->img.rect));

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}
int ft_mlx(t_map map)
{
	t_data	data;

	t_rect r = {0, 0, 10, 10, RED_PIXEL};
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (FAILURE);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (FAILURE);
	}

	/* Setup hooks */ 
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);

	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	data.img.rect = &r;
	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 33, 1L<<2, &ft_close, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (SUCCESS);
}
