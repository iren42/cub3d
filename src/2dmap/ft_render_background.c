/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_background.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 20:22:47 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 20:22:48 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_render_background(t_data *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->img.height)
	{
		j = 0;
		while (j < data->img.width)
		{
			ft_img_pix_put(&data->img, j++, i, color);
		}
		++i;
	}
}
