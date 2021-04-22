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
void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int main(int ac, char **av)
{
	int		fd;
	t_map	map;
	void	*mlx;
	t_data	img;
	void	*mlx_win;

	fd = 0;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 100, 100, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	//	ft_init_map(&map);
	//	if (ac == 1)
	//		printf("Missing map");
	//	if (ac == 2 && ft_parse_map(av[1], &map))
	//	{
	//		printf("parsing succeed\n");
	//		ft_display_tmap(map);
	//	}
	return (EXIT_SUCCESS);
}
