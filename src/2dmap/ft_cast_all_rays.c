/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast_all_rays.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 20:44:54 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 20:44:56 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static float	ft_normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

static void	ft_init_t_var(t_var_cast_ray *var)
{
	var->found_hor_wall_hit = 0;
	var->hor_wall_hit_x = 0;
	var->hor_wall_hit_y = 0;
	var->found_ver_wall_hit = 0;
	var->ver_wall_hit_x = 0;
	var->ver_wall_hit_y = 0;
}

static void	ft_cast_ray(t_data *data, t_ray *rays, float ray_angle, int id)
{
	t_var_cast_ray	var;

	ft_init_t_var(&var);
	rays[id].ray_angle = ft_normalize_angle(ray_angle);
	rays[id].is_ray_facing_down = rays[id].ray_angle > 0
		&& rays[id].ray_angle < PI;
	rays[id].is_ray_facing_right = rays[id].ray_angle < 0.5 * PI
		|| rays[id].ray_angle > 1.5 * PI;
	ft_calculate_hor_intercept(&var, rays[id], data->img.player);
	ft_calculate_hor_step(&var.xstep, &var.ystep, rays[id], rays[id].ray_angle);
	ft_find_hor_wall_hit_xy(data, &var, &rays[id]);
	ft_calculate_ver_intercept(&var, rays[id], data->img.player);
	ft_calculate_ver_step(&var.xstep, &var.ystep, rays[id], rays[id].ray_angle);
	ft_find_ver_wall_hit_xy(data, &var, &rays[id]);
	ft_fill_ray_data(&rays[id], var, data->img.player);
}

void	ft_cast_all_rays(t_data *data, t_player player, t_ray *rays)
{
	float	ray_angle;
	int		i;

	i = 0;
	if (rays != NULL)
	{
		ray_angle = player.rotation_angle - (FOV_ANGLE / 2);
		while (i < data->img.width)
		{
			ft_cast_ray(data, rays, ray_angle, i);
			ray_angle += FOV_ANGLE / data->img.width;
			i++;
		}
	}
}
