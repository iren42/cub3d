#include <X11/X.h>
#include <X11/keysym.h>
#include "cub3d.h"

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

int ft_render_tile(t_img *img, int j, int i, int color)
{
	int n;
	int m;
	int	scale;

	scale = TILE_SIZE * MINIMAP_SCALE_FACTOR;
	n = i * scale;
	while (n < (i + 1) * scale)
	{
		m = j * scale;
		while (m < (j + 1) * scale)
			ft_img_pix_put(img, m++, n, color);
		n++;
	}
	return (0);
}

void	ft_render_player(t_img *img, t_player p)
{
	printf("**player is rendered**\n");
	t_rect rec = {p.x * MINIMAP_SCALE_FACTOR,
		p.y * MINIMAP_SCALE_FACTOR, 
		p.width * MINIMAP_SCALE_FACTOR, 
		p.height * MINIMAP_SCALE_FACTOR, 
		RED_PIXEL};
	ft_render_rect(img, rec);
	ft_render_line(img, 
			MINIMAP_SCALE_FACTOR * p.x, 
			MINIMAP_SCALE_FACTOR * p.y, 
			MINIMAP_SCALE_FACTOR * p.x + cos(p.rotation_angle) * 40, // 40 is the length of the line
			MINIMAP_SCALE_FACTOR * p.y + sin(p.rotation_angle) * 40
			);

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
			tileColor = map[i][j] != 0 ? BLACK_PIXEL : WHITE_PIXEL;
			ft_render_tile(img, j, i, tileColor);
			j++;
		}
		i++;
	}
	printf("**MAP IS RENDERED\n");
}

void	ft_move_player(t_data *data)
{
	float	move_step;
	t_player	*p;

	p = data->img.player;
	p->rotation_angle += p->turn_dir * p->turn_speed;
	move_step = p->walk_dir * p->walk_speed;
	p->x += cos(p->rotation_angle) * move_step;
	p->y += sin(p->rotation_angle) * move_step;
}



int	render(t_data *data)
{
	// UPDATE HERE
	//	ft_update(data->img.player);

	if (data->win_ptr == NULL)
		return (1);
	// render things here
	ft_render_map(&data->img);
	// render_rays();
	ft_render_player(&data->img, *(data->img.player));

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
	if (keysym == XK_W || keysym == XK_w)
	{
		data->img.player->walk_dir = +1;
		printf("W pressed %d\n", data->img.player->walk_dir);
		// refresh image
		ft_refresh_img(data);
	}
	if (keysym == XK_S || keysym == XK_s)
	{
		data->img.player->walk_dir = -1;
		// refresh image
		ft_refresh_img(data);
	}
	if (keysym == XK_d || keysym == XK_D) // right
	{
		data->img.player->turn_dir = +1;
		// refresh image
		ft_refresh_img(data);
	
	}
	if (keysym == XK_A || keysym == XK_a)
	{
		data->img.player->turn_dir = -1;
		// refresh image
		ft_refresh_img(data);
	}
	return (0);
}
int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_W || keysym == XK_w)
	{
		data->img.player->walk_dir = 0;
		printf("W released %d\n", data->img.player->walk_dir);
	}
	if (keysym == XK_S || keysym == XK_s)
	{
		data->img.player->walk_dir = 0;
	}
	if (keysym == XK_d || keysym == XK_D) // right
	{
		data->img.player->turn_dir = 0;
	}
	if (keysym == XK_A || keysym == XK_a)
	{
		data->img.player->turn_dir = 0;
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
	p->walk_speed = 10;	// was 100
	p->turn_speed = 20 * (PI / 180); // was 45
}
int	ft_create_win(t_data *data)
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
	return (SUCCESS);
}
int	ft_handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	return (0);
}
int ft_mlx(t_map map)
{
	t_data	data;
	t_player p;
	int err;


	ft_setup(&p);
	data.img.player = &p;

	err = ft_create_win(&data);
	/* Setup hooks */ 
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);

	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);


	//	mlx_loop_hook(data.mlx_ptr, &render, &data);	
	mlx_loop_hook(data.mlx_ptr, &ft_handle_no_event, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_hook(data.win_ptr, 33, 1L<<2, &ft_close, &data);

	//	RENDER	
	ft_render_map(&data.img);
	ft_render_player(&data.img, *(data.img.player));
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	printf("mlx end**\n");
	return (SUCCESS);
}
