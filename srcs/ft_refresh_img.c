#include "cub3d.h"

void	ft_render_player(t_img *img, t_player p)
{
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
// map has to be a 2d dynamic array
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
}

void	ft_render_rays(t_img *img)
{
	int			i;
	t_ray		*array;
	t_player	*player;

	printf("rays rendering**\n");
	i = 0;
	player = img->player;
	array = img->rays;
	printf("NUM RAYS %d\n", NUM_RAYS);
	while (i < NUM_RAYS)
	{
	
/*		ft_render_line(img,
			player->x,
			player->y,
		array[i].wall_hit_x,
		array[i].wall_hit_y
		);
*/		
		printf("ray %d %d %f %f\n", player->x, player->y, array[i].wall_hit_x, array[i].wall_hit_y);
		i++;
	}
}

void	ft_refresh_img(t_data *data)
{	
	if (data->img.mlx_img != NULL)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->img.mlx_img = NULL;
	}

//	ft_cast_all_rays(data);
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);

	ft_render_map(&data->img);
	ft_render_player(&data->img, *data->img.player);
//	ft_render_rays(&data->img);
	if (data->img.mlx_img != NULL)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}
