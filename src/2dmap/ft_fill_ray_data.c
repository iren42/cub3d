/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_ray_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 19:41:13 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 19:53:12 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <limits.h>

static float	dist_bw_pts(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	ft_fill_ray_data(t_ray *ray, t_var_cast_ray v, t_player p)
{
	float	hhit_dist;
	float	vhit_dist;

	if (v.found_hor_wall_hit)
		hhit_dist = dist_bw_pts(p.x, p.y, v.hor_wall_hit_x, v.hor_wall_hit_y);
	else
		hhit_dist = INT_MAX;
	if (v.found_ver_wall_hit)
		vhit_dist = dist_bw_pts(p.x, p.y, v.ver_wall_hit_x, v.ver_wall_hit_y);
	else
		vhit_dist = INT_MAX;
	if (vhit_dist < hhit_dist)
	{
		ray->distance = vhit_dist;
		ray->wall_hit_x = v.ver_wall_hit_x;
		ray->wall_hit_y = v.ver_wall_hit_y;
		ray->was_hit_vertical = 1;
	}
	else
	{
		ray->distance = hhit_dist;
		ray->wall_hit_x = v.hor_wall_hit_x;
		ray->wall_hit_y = v.hor_wall_hit_y;
		ray->was_hit_vertical = 0;
	}
}
