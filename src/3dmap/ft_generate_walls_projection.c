/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_walls_projection.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 08:18:52 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 08:24:35 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calc_wall_top_bot_pix(t_data *d, t_var_generate_walls_proj *var)
{
	float	perp_distance;
	float	proj_wall_height;

	perp_distance = var->ray_distance * cos(var->ray_angle
			- var->player_rotation_angle);
	proj_wall_height = (TILE_SIZE / perp_distance)
		* var->distance_proj_plane;
	if (perp_distance == 0)
		proj_wall_height = d->img.height;
	var->wall_strip_height = proj_wall_height;
	var->wall_top_pixel = (d->img.height / 2) - ((int)proj_wall_height / 2);
	if (var->wall_top_pixel < 0)
		var->wall_top_pixel = 0;
	var->wall_bottom_pixel = (d->img.height / 2) + ((int)proj_wall_height / 2);
	if (var->wall_bottom_pixel > d->img.height)
		var->wall_bottom_pixel = d->img.height;
}

static void	ceiling_projection(t_data *d, int wall_top_pixel, int i)
{
	int	top_pixel;

	top_pixel = 0;
	if (wall_top_pixel > 0 && i > 0)
	{
		while (top_pixel < wall_top_pixel)
		{
			if (ft_get_pix_color(&d->img, i, top_pixel) != d->img.tmap->ceiling)
				ft_img_pix_put(&d->img, i, top_pixel, d->img.tmap->ceiling);
			top_pixel++;
		}
	}
}

static void	floor_projection(t_data *d, int wall_bot_pix, int i)
{
	while (wall_bot_pix < d->img.height)
	{
		if (ft_get_pix_color(&d->img, i, wall_bot_pix) != d->img.tmap->floor)
			ft_img_pix_put(&d->img, i, wall_bot_pix, d->img.tmap->floor);
		wall_bot_pix++;
	}
}

void	ft_generate_walls_projection(t_data *data)
{
	int							i;
	t_var_generate_walls_proj	var;

	i = 0;
	var.distance_proj_plane = (data->img.width / 2) / tan(FOV_ANGLE / 2);
	var.player_rotation_angle = data->img.player.rotation_angle;
	while (i < data->img.width)
	{
		var.ray_angle = data->img.rays[i].ray_angle;
		var.ray_distance = data->img.rays[i].distance;
		calc_wall_top_bot_pix(data, &var);
		ceiling_projection(data, var.wall_top_pixel, i);
		ft_walls_projection(data, var, i);
		floor_projection(data, var.wall_bottom_pixel, i);
		i++;
	}
}
