/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_mapchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 14:22:56 by iren              #+#    #+#             */
/*   Updated: 2021/06/06 14:42:07 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*fill_line(int rows, int i, char **map)
{
	char	*res;
	int		j;

	j = -1;
	res = malloc(sizeof(char) * (rows + 1));
	if (res != NULL)
	{
		while (++j < rows)
		{
			if (map[j][i] == '\0')
				res[j] = ' ';
			else
				res[j] = map[j][i];
		}
		res[j] = '\0';
	}
	return (res);
}

char	**ft_rotate_mapchar(char **map, int rows, int cols)
{
	char	**res;
	int		i;

	i = -1;
	res = malloc(sizeof(char *) * (cols + 1));
	if (res != NULL)
	{
		while (++i < cols)
		{
			res[i] = fill_line(rows, i, map);
			if (res[i] == NULL)
			{
				ft_free_previously_malloced(res, i);
				return (0);
			}
		}
		res[i] = 0;
	}
	return (res);
}
