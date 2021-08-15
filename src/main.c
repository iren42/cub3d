/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:46:11 by iren              #+#    #+#             */
/*   Updated: 2021/08/15 07:19:27 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;

	if (ac == 1)
		ft_putstr_fd("Error\nMissing map.\n", 2);
	if (ac == 2)
	{
		ft_init_tmap(&map);
		if (ft_parse_all(av[1], &map) == SUCCESS)
		{
			if (ft_mlx(&map) == SUCCESS)
				ft_putstr_fd("MLX went well\n", 1);
		}
		ft_free_tmap(&map);
	}
	return (0);
}
