/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_walls_projection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 08:05:09 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 08:18:22 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_img	*get_tex_sample(t_data *data, int i)
{
	if (!data->img.rays[i].is_ray_facing_down
		&& !data->img.rays[i].was_hit_vertical)
		return (&data->tex[So]);
	else if (data->img.rays[i].is_ray_facing_down
		&& !data->img.rays[i].was_hit_vertical)
		return (&data->tex[No]);
	else if (!data->img.rays[i].is_ray_facing_right
		&& data->img.rays[i].was_hit_vertical)
		return (&data->tex[Ea]);
	else
		return (&data->tex[We]);
}

void	ft_walls_projection(t_data *data, t_var_generate_walls_proj var, int i)
{
	int		tex_x;
	int		tex_y;
	int		j;
	int		dist_fm_top;
	t_img	*tex;

	j = var.wall_top_pixel;
	if (data->img.rays[i].was_hit_vertical)
		tex_x = (int)data->img.rays[i].wall_hit_y % TILE_SIZE;
	else
		tex_x = (int)data->img.rays[i].wall_hit_x % TILE_SIZE;
	while (j < var.wall_bottom_pixel)
	{
		dist_fm_top = j + (var.wall_strip_height / 2) - (data->img.height / 2);
		 tex = get_tex_sample(data, i);
		 tex_y = dist_fm_top * ((float)tex->height / var.wall_strip_height);
		if (ft_get_pix_color(&data->img, i, j)
			!= ft_get_pix_color(tex, tex_x, tex_y))
			ft_img_pix_put(&data->img, i, j,
				ft_get_pix_color(tex, tex_x, tex_y));
		j++;
	}
}
