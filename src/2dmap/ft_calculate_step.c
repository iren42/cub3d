/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_step.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 20:31:09 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 20:38:42 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calculate_hor_step(float *xstep, float *ystep,
	t_ray ray, float ray_angle)
{
	*ystep = TILE_SIZE;
	if (!ray.is_ray_facing_down)
		*ystep *= -1;
	*xstep = TILE_SIZE / tan(ray_angle);
	if (!ray.is_ray_facing_right && *xstep > 0)
		*xstep *= -1;
	if (ray.is_ray_facing_right && *xstep < 0)
		*xstep *= -1;
}

void	ft_calculate_ver_step(float *xstep, float *ystep,
	t_ray ray, float ray_angle)
{
	*xstep = TILE_SIZE;
	if (!ray.is_ray_facing_right)
		*xstep *= -1;
	*ystep = TILE_SIZE * tan(ray_angle);
	if (!ray.is_ray_facing_down && *ystep > 0)
		*ystep *= -1;
	if (ray.is_ray_facing_down && *ystep < 0)
		*ystep *= -1;
}
