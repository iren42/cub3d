/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:14:11 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 14:30:41 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_tmap(t_map *tmap)
{
	tmap->error = 0;
	tmap->texture = malloc(sizeof(char *) * 4);
	if (tmap->texture != NULL)
	{
		tmap->texture[no] = 0;
		tmap->texture[so] = 0;
		tmap->texture[ea] = 0;
		tmap->texture[we] = 0;
	}
	tmap->floor = -1;
	tmap->ceiling = -1;
	tmap->map = 0;
	tmap->rows = 0;
	tmap->cols = 0;
}
