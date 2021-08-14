/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refresh_img.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 23:10:16 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 20:45:24 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	render_player(t_img *img, t_player p)
{
	t_point	a;
	t_point	b;
	t_rect	rec;

	a.x = MINIMAP_SCALE_FACTOR * p.x;
	a.y = MINIMAP_SCALE_FACTOR * p.y;
	b.x = MINIMAP_SCALE_FACTOR
		* (p.x + cos(p.rotation_angle) * 50);
	b.y = MINIMAP_SCALE_FACTOR
		* (p.y + sin(p.rotation_angle) * 50);
	rec.x = p.x * MINIMAP_SCALE_FACTOR;
	rec.y = p.y * MINIMAP_SCALE_FACTOR;
	rec.width = p.width * MINIMAP_SCALE_FACTOR;
	rec.height = p.height * MINIMAP_SCALE_FACTOR;
	rec.color = RED_PIXEL;
	if (a.x - rec.width >= 0 && a.x + rec.width <= img->width
		&& a.y - rec.height >= 0 && a.y + rec.height <= img->height
		&& b.x - rec.width >= 0 && b.x + rec.width <= img->width
		&& b.y - rec.height >= 0 && b.y + rec.height <= img->height)
	{
		ft_render_rect(img, rec);
		ft_render_line(img, a, b);
	}
}

static int	render_tile(t_img *img, int j, int i, int color)
{
	int	n;
	int	m;
	int	scale;

	scale = TILE_SIZE * MINIMAP_SCALE_FACTOR;
	n = i * scale;
	if (color >= 0)
	{
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
	}
	return (0);
}

static void	render_map(t_img *img)
{
	int	i;
	int	j;

	i = 0;
	if (img->tmap->map != NULL)
	{
		while (i < img->tmap->rows
			&& i * TILE_SIZE * MINIMAP_SCALE_FACTOR < img->height)
		{
			j = 0;
			while (j < img->tmap->cols
				&& j * TILE_SIZE * MINIMAP_SCALE_FACTOR < img->width)
			{
				if (img->tmap->map[i][j] == '1')
					render_tile(img, j, i, GREEN_PIXEL);
				else
					render_tile(img, j, i, BLACK_PIXEL);
				j++;
			}
			i++;
		}
	}
}

int	ft_refresh_img(t_data *d)
{	
	ft_cast_all_rays(d, d->img.player, d->img.rays);
	ft_generate_walls_projection(d);
	render_map(&d->img);
	render_player(&d->img, d->img.player);
	if (d->img.mlx_img != NULL && d->win_ptr != NULL && d->mlx_ptr != NULL)
		mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img.mlx_img, 0, 0);
	return (0);
}
