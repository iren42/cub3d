/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_proh_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 04:03:44 by iren              #+#    #+#             */
/*   Updated: 2021/08/15 04:53:45 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_middle(char **map, int rows, int cols)
{
	int	i;
	int	j;

	j = 0;
	while (++j < rows - 2)
	{
		i = 0;
		while (++i < cols - 2)
		{
			if (map[j][i] == 'b')
			{
				if ((map[j - 1][i] != 'b' && map[j - 1][i] != '1')
						|| (map[j + 1][i] != 'b' && map[j + 1][i] != '1')
						|| (map[j][i - 1] != 'b' && map[j][i - 1] != '1')
						|| (map[j][i + 1] != 'b' && map[j][i + 1] != '1'))
					return (1);
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
		if (map[j][0] == 'b')
			return (1);
		if (map[j][cols - 1] == 'b')
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
		if (map[0][i] == 'b')
			return (1);
		if (map[rows - 1][i] == 'b')
			return (1);
		i++;
	}
	return (0);
}

int	ft_find_proh_b(char **map, int rows, int cols)
{
	return (check_top_bot_lines(map, rows, cols)
		|| check_left_right_lines(map, rows, cols)
		|| check_middle(map, rows, cols));
}
