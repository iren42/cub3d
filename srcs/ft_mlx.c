#include <X11/X.h>
#include <X11/keysym.h>
#include "cub3d.h"


#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

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
int render_tile(t_img *img, int j, int i, int color)
{
	int n;
	int m;

	n = i * TILE_SIZE;
	while (n < (i + 1) * TILE_SIZE)
	{
		m = j * TILE_SIZE;
		while (m < (j + 1) * TILE_SIZE)
			ft_img_pix_put(img, m++, n, color);
		n++;
	}
	return (0);
}

// TODO: t_map as 2nd param
void ft_render_map(t_img *img) {
	int tileColor;
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < MAP_NUM_ROWS)
	{
		j= 0;
		while (j < MAP_NUM_COLS)
		{
			tileColor = map[i][j] != 0 ? RED_PIXEL : WHITE_PIXEL;
			render_tile(img, j, i, tileColor);
			j++;
		}
		i++;
	}
}
int	render(t_data *data)
{
	// UPDATE HERE
	//	ft_update(data->img.player);

	if (data->win_ptr == NULL)
		return (1);
	// render things here
	render_background(&data->img, GREEN_PIXEL);
	ft_render_map(&data->img);
	// render_rays();
	// render_player();

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

// Start position of the player
void	ft_setup(t_player *p)
{
	p->x = WINDOW_WIDTH / 2;
	p->y = WINDOW_HEIGHT / 2;
	p->width = 5;
	p->height= 5;
	p->turn_dir = 0;
	p->walk_dir = 0;
	p->rotation_angle = PI / 2;
	p->walk_speed = 100;
	p->turn_speed = 45 * (PI / 100);
}

int ft_mlx(t_map map)
{
	t_data	data;

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
