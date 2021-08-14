/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:46:11 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 14:03:31 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_map	map;

	if (ac == 1)
		perror("Error.\nMissing map.\n");
	if (ac == 2)
	{
		ft_init_tmap(&map);
		if (ft_parse_all(av[1], &map) == SUCCESS)
		{
			if (ft_mlx(&map) == SUCCESS)
				printf("MLX went well\n");
		}
		ft_free_tmap(&map);
	}
	return (0);
}
