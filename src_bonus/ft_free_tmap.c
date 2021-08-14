/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 22:34:25 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 14:31:15 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_tmap(t_map *tmap)
{
	int	i;

	i = -1;
	if (tmap != NULL)
	{
		if (tmap->texture[no] != 0)
			free(tmap->texture[no]);
		if (tmap->texture[so] != 0)
			free(tmap->texture[so]);
		if (tmap->texture[we] != 0)
			free(tmap->texture[we]);
		if (tmap->texture[ea] != 0)
			free(tmap->texture[ea]);
		free(tmap->texture);
		if (tmap->map != 0)
		{
			while (tmap->map[++i] != 0)
				free(tmap->map[i]);
			free(tmap->map);
			tmap->map = 0;
		}
	}
}
