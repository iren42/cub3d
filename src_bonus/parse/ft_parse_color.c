/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 15:55:49 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 19:14:32 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_out_of_boundary(int n)
{
	if (n < 0 || n > 255)
		return (1);
	return (0);
}

static void	ft_init(int *n1, int *n2, int *n3)
{
	*n1 = -1;
	*n2 = -1;
	*n3 = -1;
}

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	parse_nbs(int *n1, int *n2, int *n3, char *line)
{
	unsigned int	i;

	i = ft_skip_spaces(line, 1);
	*n1 = ft_parse_nb(line, &i, ',');
	*n2 = ft_parse_nb(line, &i, ',');
	*n3 = ft_parse_nb(line, &i, ',');
	if (line[i] != '\0' || is_out_of_boundary(*n1)
		|| is_out_of_boundary(*n2) || is_out_of_boundary(*n3))
	{
		perror("Error.\nColors should be in range [0, 255].\n");
		return (-1);
	}
	return (0);
}

void	ft_parse_color(char *line, t_map *map)
{
	int	n1;
	int	n2;
	int	n3;
	int	trgb;
	int	err;

	if ((line[0] == 'F' && map->floor == -1 && line[1] == ' ')
		|| (line[0] == 'C' && map->ceiling == -1 && line[1] == ' '))
	{
		ft_init(&n1, &n2, &n3);
		err = parse_nbs(&n1, &n2, &n3, line);
		if (err == -1)
			map->error = -1;
		trgb = create_trgb(0, n1, n2, n3);
		if (line[0] == 'F')
			map->floor = trgb;
		else
			map->ceiling = trgb;
	}
	else if (line[0] == 'F' || line[0] == 'C')
	{
		map->error = -1;
		perror("Error.\nTake a look on colors in file descriptor.\n");
	}
}
