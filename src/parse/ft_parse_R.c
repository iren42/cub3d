/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_R.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 00:39:31 by iren              #+#    #+#             */
/*   Updated: 2021/06/06 23:57:24 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_parse_R(char *line, t_map *map)
{
	int		i;

	i = 0;
	if (line[0] == 'R' && line[1] == ' ' 
			&& map->res_x == 0 && map->res_y == 0)
	{
		i = ft_skip_spaces(line, ++i);
		map->res_x = ft_parse_nb(line, &i, ' ');
		map->res_y = ft_parse_nb(line, &i, ' ');
		if (line[i] != '\0')
			map->error = 1;
	//	printf("res map error %d, x = %d, y = %d\n", map->error, map->res_x, map->res_y);
	}
}
