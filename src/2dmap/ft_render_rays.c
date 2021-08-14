/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 09:06:50 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 18:06:49 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_render_rays(t_data *data)
{
	int		i;
	t_point	a;
	t_point	b;

	i = 0;
	while (i < data->img.width)
	{
		a.x = MINIMAP_SCALE_FACTOR * data->img.player.x;
		a.y = MINIMAP_SCALE_FACTOR * data->img.player.y;
		b.x = MINIMAP_SCALE_FACTOR * data->img.rays[i].wall_hit_x;
		b.y = MINIMAP_SCALE_FACTOR * data->img.rays[i].wall_hit_y;
		ft_render_line(&data->img, a, b);
		i++;
	}
}
