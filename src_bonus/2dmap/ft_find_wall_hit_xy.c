/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_wall_hit_xy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 21:11:00 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 08:04:42 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_value(int condition, float next_touch, float *pt_tocheck)
{
	*pt_tocheck = next_touch;
	if (condition)
		*pt_tocheck += -1;
}

void	ft_find_hor_wall_hit_xy(t_data *data, t_var_cast_ray *var, t_ray *ray)
{
	float	next_hor_touch_x;
	float	next_hor_touch_y;
	float	y_tocheck;
	float	x_tocheck;

	next_hor_touch_x = var->xintercept;
	next_hor_touch_y = var->yintercept;
	while (next_hor_touch_x >= 0 && next_hor_touch_x <= data->img.width
		&& next_hor_touch_y >= 0 && next_hor_touch_y <= data->img.height)
	{
		x_tocheck = next_hor_touch_x;
		get_value(!ray->is_ray_facing_down, next_hor_touch_y, &y_tocheck);
		if (ft_map_has_wall_at(data, x_tocheck, y_tocheck))
		{
			var->hor_wall_hit_x = next_hor_touch_x;
			var->hor_wall_hit_y = next_hor_touch_y;
			var->found_hor_wall_hit = 1;
			break ;
		}
		else
		{
			next_hor_touch_x += var->xstep;
			next_hor_touch_y += var->ystep;
		}
	}
}

void	ft_find_ver_wall_hit_xy(t_data *data, t_var_cast_ray *var, t_ray *ray)
{
	float	next_ver_touch_x;
	float	next_ver_touch_y;
	float	x_tocheck;
	float	y_tocheck;

	next_ver_touch_x = var->xintercept;
	next_ver_touch_y = var->yintercept;
	while (next_ver_touch_x >= 0 && next_ver_touch_x <= data->img.width
		&& next_ver_touch_y >= 0 && next_ver_touch_y <= data->img.height)
	{
		get_value(!ray->is_ray_facing_right, next_ver_touch_x, &x_tocheck);
		y_tocheck = next_ver_touch_y;
		if (ft_map_has_wall_at(data, x_tocheck, y_tocheck))
		{
			var->ver_wall_hit_x = next_ver_touch_x;
			var->ver_wall_hit_y = next_ver_touch_y;
			var->found_ver_wall_hit = 1;
			break ;
		}
		else
		{
			next_ver_touch_x += var->xstep;
			next_ver_touch_y += var->ystep;
		}
	}
}
