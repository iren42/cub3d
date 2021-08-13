/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 09:06:50 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 09:07:02 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_render_rays(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->img.width)
	{
		ft_render_line(&data->img,
				MINIMAP_SCALE_FACTOR * data->img.player.x,
				MINIMAP_SCALE_FACTOR * data->img.player.y,
				MINIMAP_SCALE_FACTOR * data->img.rays[i].wall_hit_x,
				MINIMAP_SCALE_FACTOR * data->img.rays[i].wall_hit_y
				);
		//		printf("rays[%d] %f %f\n",i, img->rays[i].wall_hit_x, img->rays[i].wall_hit_y);
		i++;
	}
}
