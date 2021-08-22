/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_wall_hit_xy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 21:11:00 by iren              #+#    #+#             */
/*   Updated: 2021/08/22 15:00:07 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	init(int cond, float nxt_tc1, float nxt_touch2, float *p_check)
{
	*p_check = nxt_tc1;
	if (cond)
		*p_check += -1;
	return (nxt_touch2);
}

void	ft_find_hor_wall_hit_xy(t_data *data, t_var_cast_ray *var, t_ray *ray)
{
	float	next_htx;
	float	next_hty;
	float	y_check;
	float	x_check;

	next_htx = var->xintercept;
	next_hty = var->yintercept;
	while (next_htx >= 0 && next_hty >= 0
		&& next_htx <= data->img.tmap->cols * TILE_SIZE
		&& next_hty <= data->img.tmap->rows * TILE_SIZE)
	{
		x_check = init(!ray->is_ray_facing_down, next_hty, next_htx, &y_check);
		if (ft_map_has_wall_at(data, x_check, y_check))
		{
			var->hor_wall_hit_x = next_htx;
			var->hor_wall_hit_y = next_hty;
			var->found_hor_wall_hit = 1;
			break ;
		}
		else
		{
			next_htx += var->xstep;
			next_hty += var->ystep;
		}
	}
}

void	ft_find_ver_wall_hit_xy(t_data *data, t_var_cast_ray *var, t_ray *ray)
{
	float	next_vtx;
	float	next_vty;
	float	x_check;
	float	y_check;

	next_vtx = var->xintercept;
	next_vty = var->yintercept;
	while (next_vtx >= 0 && next_vty >= 0
		&& next_vtx <= data->img.tmap->cols * TILE_SIZE
		&& next_vty <= data->img.tmap->rows * TILE_SIZE)
	{
		y_check = init(!ray->is_ray_facing_right, next_vtx, next_vty, &x_check);
		if (ft_map_has_wall_at(data, x_check, y_check))
		{
			var->ver_wall_hit_x = next_vtx;
			var->ver_wall_hit_y = next_vty;
			var->found_ver_wall_hit = 1;
			break ;
		}
		else
		{
			next_vtx += var->xstep;
			next_vty += var->ystep;
		}
	}
}
