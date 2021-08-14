/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vim ft_get_pix_color.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/14 08:06:02 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 08:06:25 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_get_pix_color(t_img *img, int x, int y)
{
	int	a;

	a = 0x0;
	if (x >= 0 && x < img->width && y >= 0 && y <= img->height)
		a = *(int *)(img->addr + (x + y * img->width) * img->bpp / 8);
	return (a);
}
