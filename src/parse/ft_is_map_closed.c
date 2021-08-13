/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 00:38:25 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 19:33:44 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_spread_b(char **map, t_var_spread_b var, int x, int y)
{
	if (y >= 0 && y <= var.rows - 1 && x >= 0 && x <= var.cols - 1)
	{
		if (map[y][x] == '0')
		{
			map[y][x] = 'b';
			ft_spread_b(map, var, x + 1, y);
			ft_spread_b(map, var, x - 1, y);
			ft_spread_b(map, var, x, y + 1);
			ft_spread_b(map, var, x, y - 1);
		}
	}
}

static int	find_b_in_proh_area(char **map, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (map[0][i] != '\0')
		if (map[0][i++] == 'b')
			return (1);
	i = 0;
	while (map[rows - 1][i] != '\0')
		if (map[rows - 1][i++] == 'b')
			return (1);
	j = 0;
	while (++j < rows - 1)
	{
		i = 0;
		if (map[j][0] == 'b')
			return (1);
		while (map[j][i] != '\0' && map[j][i] != ' ')
			i++;
		if (i > 0)
			if (map[j][i - 1] == 'b')
				return (1);
	}
	return (0);
}

static void	ft_init_var(t_var_spread_b *var, int rows, int cols,
		int *b_is_found)
{
	var->rows = rows;
	var->cols = cols;
	*b_is_found = 0;
}

static void	disable_diag_mvmt(t_map *tmap, char **ref)
{
	int	i;
	int	j;

	j = -1;
	while (++j < tmap->rows)
	{
		i = -1;
		while (++i < tmap->cols)
		{
			if (ref[j][i] == '0')
				tmap->map[j][i] = ' ';
		}
	}
}

int	ft_is_map_closed(t_map *tmap, int px, int py)
{
	char			**cp;
	char			**cp_rot;
	int				b_is_found;
	t_var_spread_b	var;

	ft_init_var(&var, tmap->rows, tmap->cols, &b_is_found);
	cp = ft_copy_mapchar(tmap->map, tmap->rows, tmap->cols);
	if (cp == NULL)
		return (FAILURE);
	if (py < tmap->rows && py > -1 && px < tmap->cols && px > -1)
		cp[py][px] = '0';
	ft_spread_b(cp, var, px, py);
	cp_rot = ft_rotate_mapchar(cp, tmap->rows, tmap->cols);
	if (cp_rot == NULL)
		return (FAILURE);
	b_is_found = find_b_in_proh_area(cp, tmap->rows)
		|| find_b_in_proh_area(cp_rot, tmap->cols)
		|| find_b_in_proh_area(ft_mirror(cp, tmap->rows, tmap->cols),
			tmap->rows)
		|| find_b_in_proh_area(ft_mirror(cp_rot, tmap->cols, tmap->rows),
			tmap->cols);
	disable_diag_mvmt(tmap, cp);
	ft_free_mapchar(cp);
	ft_free_mapchar(cp_rot);
	return (!b_is_found);
}
