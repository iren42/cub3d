/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 19:40:13 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 21:10:20 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_render_line(t_img *img, t_point a, t_point b)
{
	int		i;
	double	x;
	double	y;
	double	length;

	y = b.y - a.y;
	x = b.x - a.x;
	length = sqrt(x * x + y * y);
	x = a.x;
	y = a.y;
	i = 0;
	while (i < length)
	{
		ft_img_pix_put(img, x, y, RED_PIXEL);
		x += (b.x - a.x) / length;
		y += (b.y - a.y) / length;
		i++;
	}
	return (SUCCESS);
}
