/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 22:14:11 by iren              #+#    #+#             */
/*   Updated: 2021/04/18 00:43:21 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_map(t_map *map)
{
	map->error = 0;
	map->res_x = 0;
	map->res_y = 0;
	map->texture = malloc(sizeof(char*) * 5);
	if (map->texture != NULL)
	{
		map->texture[No] = 0;
		map->texture[So] = 0;
		map->texture[Ea] = 0;
		map->texture[We] = 0;
		map->texture[Sp] = 0;
	}
	map->floor = 0;
	map->ceiling = 0;
}
