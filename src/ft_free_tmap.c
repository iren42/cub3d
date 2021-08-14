/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 22:34:25 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 12:54:13 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_tmap(t_map *tmap)
{
	int	i;

	i = -1;
	if (tmap != NULL)
	{
		if (tmap->texture[No] != 0)
			free(tmap->texture[No]);
		if (tmap->texture[So] != 0)
			free(tmap->texture[So]);
		if (tmap->texture[We] != 0)
			free(tmap->texture[We]);
		if (tmap->texture[Ea] != 0)
			free(tmap->texture[Ea]);
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
