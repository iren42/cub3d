/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:46:11 by iren              #+#    #+#             */
/*   Updated: 2021/07/25 18:12:16 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
int main(int ac, char **av)
{
	int		fd;
	t_map	map;
	int 	err;

	fd = 0;
	(void)fd;
	ft_init_tmap(&map);
	if (ac == 1)
		printf("Missing map");
	if (ac == 2 && ft_parse_all(av[1], &map) == SUCCESS)
	{
		printf("fd's parsing succeed\nLa map fd :\n");
		ft_display_tmap_map(map);
		err = ft_mlx(&map);
		if (err == SUCCESS)
			printf("MLX went well\n");
		ft_free_tmap(&map);
	}
	return (EXIT_SUCCESS);
}
