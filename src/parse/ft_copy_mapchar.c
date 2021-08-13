/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_mapchar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 19:36:21 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 19:36:24 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_copy_mapchar(char **map, int nb_rows, int nb_cols)
{
	char	**res;
	int		i;
	int		j;

	res = malloc(sizeof(char *) * (nb_rows + 1));
	if (res == NULL)
		return (0);
	i = 0;
	while (i < nb_rows)
	{
		j = -1;
		res[i] = malloc(sizeof(char) * (nb_cols + 1));
		if (res[i] == NULL)
		{
			ft_free_previously_malloced(res, i);
			return (0);
		}
		while (++j < nb_cols && map[i][j] != '\0')
			res[i][j] = map[i][j];
		while (j < nb_cols)
			res[i][j++] = ' ';
		res[i++][nb_cols] = '\0';
	}
	res[i] = 0;
	return (res);
}
