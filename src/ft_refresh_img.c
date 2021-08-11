/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refresh_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 23:10:16 by iren              #+#    #+#             */
/*   Updated: 2021/08/11 15:44:57 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_render_player(t_img *img, t_player p)
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
			MINIMAP_SCALE_FACTOR * (p.x + cos(p.rotation_angle) * (TILE_SIZE / 2)), // (TILE_SIZE / 2) is the length of the line
			MINIMAP_SCALE_FACTOR * (p.y + sin(p.rotation_angle) * (TILE_SIZE / 2))
			);

}

static int ft_render_tile(t_img *img, int j, int i, int color)
{
	int n;
	int m;
	int	scale;

	scale = TILE_SIZE * MINIMAP_SCALE_FACTOR;
	n = i * scale;
	if (color >= 0)
		while (n < (i + 1) * scale)
		{
			m = j * scale;
			while (m < (j + 1) * scale)
			{
				if (ft_get_pix_color(img, m, n) != color)
					ft_img_pix_put(img, m, n, color);
				m++;
			}
			n++;
		}
	return (0);
}
// map has to be a 2d array
static void ft_render_map(t_img *img) {
	//	int tileColor;
	int i;
	int j;

	i = -1;
	//	printf("rows cols %d %d\n", img->tmap->rows, img->tmap->cols);
	//	ft_display_tmap_map(*img->tmap);
	if (img->tmap->map != NULL)
		while (++i < img->tmap->rows) // MAP_NUM_ROWS
		{
			j = -1;
			while (++j < img->tmap->cols) // MAP_NUM_COLS
			{
				if (img->tmap->map[i][j] == '1')
					ft_render_tile(img, j, i, GREEN_PIXEL);
				else
					ft_render_tile(img, j, i, BLACK_PIXEL);
			}
		}
}

static void	ft_render_rays(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->img.width)
	{
		ft_render_line(&data->img,
				MINIMAP_SCALE_FACTOR * data->img.player.x,
				MINIMAP_SCALE_FACTOR * data->img.player.y,
				MINIMAP_SCALE_FACTOR * data->img.rays[i].wall_hit_x,
				MINIMAP_SCALE_FACTOR * data->img.rays[i].wall_hit_y
				);
		//		printf("rays[%d] %f %f\n",i, img->rays[i].wall_hit_x, img->rays[i].wall_hit_y);
		i++;
	}
}

void	ft_refresh_img(t_data *data)
{	
	//	if (data->mlx_ptr != NULL && data->win_ptr != NULL)
	//		mlx_clear_window(data->mlx_ptr, data->win_ptr);
	ft_cast_all_rays(data, data->img.player, data->img.rays);
	// Render 3D map
	ft_generate_walls_projection(data);
	// Render minimap
	ft_render_map(&data->img);
	ft_render_player(&data->img, data->img.player);
	//	ft_render_rays(data); // BIG LAG
	if (data->img.mlx_img != NULL && data->win_ptr != NULL && data->mlx_ptr != NULL)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
}
