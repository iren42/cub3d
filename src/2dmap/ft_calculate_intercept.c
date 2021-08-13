/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate_intercept.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 20:24:30 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 20:30:32 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_calculate_hor_intercept(t_var_cast_ray *var, t_ray ray, t_player p)
{
	var->yintercept = floor(p.y / TILE_SIZE) * TILE_SIZE;
	if (ray.is_ray_facing_down)
		var->yintercept += TILE_SIZE;
	var->xintercept = p.x + (var->yintercept - p.y) / tan(ray.ray_angle);
}

void	ft_calculate_ver_intercept(t_var_cast_ray *var, t_ray ray, t_player p)
{
	var->xintercept = floor(p.x / TILE_SIZE) * TILE_SIZE;
	if (ray.is_ray_facing_right)
		var->xintercept += TILE_SIZE;
	var->yintercept = p.y + (var->xintercept - p.x) * tan(ray.ray_angle);
}
