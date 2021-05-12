/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:46:11 by iren              #+#    #+#             */
/*   Updated: 2021/04/18 16:54:47 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_display_tmap(t_map map)
{
	printf("res_x = %d\n", map.res_x);
	printf("res_y = %d\n", map.res_y);
	printf("no = %s\n", map.no);
	printf("so = %s\n", map.so);
	printf("ea = %s\n", map.ea);
	printf("we = %s\n", map.we);
	printf("error = %d\n", map.error);
}

int main(int ac, char **av)
{
	int		fd;
	t_map	map;
	int 	err;

	fd = 0;
	(void)fd;
	ft_init_map(&map);
	if (ac == 1)
		printf("Missing map");
	if (ac == 2 && ft_parse_map(av[1], &map))
	{
		printf("parsing succeed\n");
		err = ft_mlx(map);
		if (err == SUCCESS)
			printf("MLX went well\n");
	}
	return (EXIT_SUCCESS);
}
