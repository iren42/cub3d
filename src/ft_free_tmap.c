/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 22:34:25 by iren              #+#    #+#             */
/*   Updated: 2021/08/12 23:35:53 by iren             ###   ########.fr       */
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
	//		ft_display_tmap_map(*tmap);
			while (tmap->map[++i] != 0)
			{
				printf("string freed : %s\n", tmap->map[i]);
				free(tmap->map[i]);
			}
			free(tmap->map);
			tmap->map = 0;
		}
	}
}
