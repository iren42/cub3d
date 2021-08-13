/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_rect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 19:39:23 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 19:39:59 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_render_rect(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	if (rect.x > 0 && rect.y > 0)
	{
		i = rect.y;
		while (i < rect.y + rect.height)
		{
			j = rect.x;
			while (j < rect.x + rect.width)
				ft_img_pix_put(img, j++, i, rect.color);
			++i;
		}
	}
	return (0);
}
