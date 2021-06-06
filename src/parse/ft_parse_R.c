/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_R.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 00:39:31 by iren              #+#    #+#             */
/*   Updated: 2021/06/06 14:04:11 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_calc_line_length(char *res)
{
	int len;

	len = 0;
	if (res)
	{
		while (res[len] && (res[len] != ' '))
		{
			len++;
		}
	}
	return (len);
}

void	ft_parse_R(char *line, t_map *map)
{
	int		i;

	i = 0;
	if (line[0] == 'R' && line[1] == ' ' 
			&& map->res_x == 0 && map->res_y == 0)
	{
		i = ft_skip_spaces(line, ++i);
		if (ft_strchr("+-0123456789", line[i]) != NULL)
			map->res_x = ft_atoi(&line[i]);
		i += ft_calc_line_length(&line[i]);
		i = ft_skip_spaces(line, i);
		if (ft_strchr("+-0123456789", line[i]) != NULL)
			map->res_y = ft_atoi(&line[i]);
		// to make sure that there's no illegal character after
		i += ft_calc_line_length(&line[i]);
		i = ft_skip_spaces(line, i);
		if (line[i] != '\0')
			map->error = 1;
		printf("map error %d\n", map->error);
	}
	// Disallow double definition of resolution
}
