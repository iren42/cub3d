/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_proh_zero.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:03:44 by iren              #+#    #+#             */
/*   Updated: 2021/08/15 10:50:43 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_middle(char **map, int rows, int cols)
{
	int	i;
	int	j;

	j = 0;
	while (++j < rows - 1)
	{
		i = 0;
		while (++i < cols - 1)
		{
			if (map[j][i] == '0')
			{
				if (ft_strchr("01", map[j - 1][i]) == 0
					|| ft_strchr("01", map[j + 1][i]) == 0
					|| ft_strchr("01", map[j][i + 1]) == 0
					|| ft_strchr("01", map[j][i - 1]) == 0)
				{
					return (1);
				}
			}
		}
	}
	return (0);
}

static int	check_left_right_lines(char **map, int rows, int cols)
{
	int	j;

	j = 0;
	while (j < rows)
	{
		if (map[j][0] == '0')
			return (1);
		if (map[j][cols - 1] == '0')
			return (1);
		j++;
	}
	return (0);
}

static int	check_top_bot_lines(char **map, int rows, int cols)
{
	int	i;

	i = 0;
	while (i < cols - 1)
	{
		if (map[0][i] == '0')
			return (1);
		if (map[rows - 1][i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	ft_find_proh_zero(t_map *tmap, int px, int py)
{
	char	**copy;
	int		zero_found;

	zero_found = 0;
	copy = 0;
	copy = ft_copy_mapchar(tmap->map, tmap->rows, tmap->cols);
	if (copy == NULL)
		return (FAILURE);
	if (py < tmap->rows && py > -1 && px < tmap->cols && px > -1)
		copy[py][px] = '0';
	zero_found = (check_top_bot_lines(copy, tmap->rows, tmap->cols)
			|| check_left_right_lines(copy, tmap->rows, tmap->cols)
			|| check_middle(copy, tmap->rows, tmap->cols));
	ft_free_mapchar(copy);
	return (zero_found);
}
