/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_tmap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:14:11 by iren              #+#    #+#             */
/*   Updated: 2021/07/24 16:23:15 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_tmap(t_map *map)
{
	map->error = 0;
//	map->res_x = 0;
//	map->res_y = 0;
	map->texture = malloc(sizeof(char*) * 5);
	if (map->texture != NULL)
	{
		map->texture[No] = 0;
		map->texture[So] = 0;
		map->texture[Ea] = 0;
		map->texture[We] = 0;
		map->texture[Sp] = 0;
	}
	map->floor = -1;
	map->ceiling = -1;
}
