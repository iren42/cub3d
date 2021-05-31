/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 00:38:25 by iren              #+#    #+#             */
/*   Updated: 2021/05/31 01:58:10 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_spread_b(char **map, t_var_spread_b var, int x, int y)
{
	if (x >= 0 && x <= var.rows - 1 && y >= 0 && y <= var.cols - 1)
	{
		if (map[x][y] == '0' || map[x][y] == '2' )
		{
			map[x][y] = 'b';
			ft_spread_b(map, var, x + 1, y);
			ft_spread_b(map, var, x - 1, y);
			ft_spread_b(map, var, x, y + 1);
			ft_spread_b(map, var, x, y - 1);
		}
	}
}

static char	**rotate_mapchar(char **map, int rows, int cols)
{
	char	**res;
	int		i;
	int		j;

	i = -1;
	res = malloc(sizeof(char *) * (cols + 1));
	if (res != NULL)
	{
		while (++i < cols)
		{
			j = -1;
			res[i] = malloc(sizeof(char) * (rows + 1));
			while (++j < rows)
			{
				if (map[j][i] == '\0')
					res[i][j] = ' ';
				else
					res[i][j] = map[j][i];
			}
			res[i][j] = '\0';
		}
		res[i] = 0;
	}
	return (res);
}

static int	find_b_in_proh_area(char **map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (map[0][i] != '\0')
		if (map[0][i++] == 'b')
			return (1);
	while (j < rows - 1 && i < cols - 1)
	{
		i = 0;
		if (map[j][0] == 'b')
			return (1);
		while (map[j][i] != '\0' && map[j][i] != ' ')
			i++;
		if (map[j][i - 1] == 'b')
			return (1);
		j++;
	}
	i = 0;
	while (map[rows - 1][i] != '\0')
		if (map[rows - 1][i++] == 'b')
			return (1);
	return (0);
}

static void	ft_init_var(t_var_spread_b *var, int rows, int cols,
		int *b_is_found)
{
	var->rows = rows;
	var->cols = cols;
	*b_is_found = 0;
}

int	ft_is_map_closed(t_map map, int px, int py)
{
	char			**cp;
	char			**cp_rot;
	int				b_is_found;
	t_var_spread_b	var;

	ft_init_var(&var, map.rows, map.cols, &b_is_found);
	cp = ft_copy_mapchar(map.map, map.rows, map.cols);
	if (cp == NULL)
		return (FAILURE);
	if (px < map.rows && px > -1 && py < map.cols && py > -1)
		cp[px][py] = '0';
	ft_spread_b(cp, var, px, py);
	cp_rot = rotate_mapchar(cp, map.rows, map.cols);
	if (cp_rot == NULL)
		return (FAILURE);
	ft_display_chararray(cp_rot);
	b_is_found = find_b_in_proh_area(cp, map.rows, map.cols)
		|| find_b_in_proh_area(cp_rot, map.cols, map.rows)
		|| find_b_in_proh_area(ft_mirror(cp, map.rows, map.cols),
			map.rows, map.cols)
		|| find_b_in_proh_area(ft_mirror(cp_rot, map.cols, map.rows),
			map.cols, map.rows);
	ft_free_mapchar(cp);
	ft_free_mapchar(cp_rot);
	return (!b_is_found);
}
