/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 23:08:32 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 20:54:04 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_setup_player(t_data *d)
{
	if (d->img.tmap->map[d->img.tmap->py][d->img.tmap->px] == 'S')
		d->img.player.rotation_angle = PI / 2;
	else if (d->img.tmap->map[d->img.tmap->py][d->img.tmap->px] == 'N')
		d->img.player.rotation_angle = 3 * PI / 2;
	else if (d->img.tmap->map[d->img.tmap->py][d->img.tmap->px] == 'W')
		d->img.player.rotation_angle = PI;
	else
		d->img.player.rotation_angle = 0;
	d->img.tmap->map[d->img.tmap->py][d->img.tmap->px] = '0';
	d->img.player.x = (TILE_SIZE * (d->img.tmap->px + 0.5));
	d->img.player.y = (TILE_SIZE * (d->img.tmap->py + 0.5));
	d->img.player.width = TILE_SIZE * 0.4;
	d->img.player.height = TILE_SIZE * 0.4;
	d->img.player.turn_dir = 0;
	d->img.player.walk_dir = 0;
	d->img.player.cam_dir = 0;
	d->img.player.walk_speed = 10;
	d->img.player.turn_speed = 20 * (PI / 180);
	d->img.rays = malloc(sizeof(t_ray) * d->img.width);
	if (d->img.rays == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	create_new_img(t_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, data->img.width,
			data->img.height);
	if (data->img.mlx_img == NULL)
	{
		perror("Error.\nCould not create a new image.\n");
		return (FAILURE);
	}
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	data->img.rays = 0;
	return (SUCCESS);
}

int	ft_create_mlx_win_and_img(t_data *d, t_map *map)
{
	d->mlx_ptr = 0;
	d->win_ptr = 0;
	d->mlx_ptr = mlx_init();
	d->img.mlx_img = 0;
	if (d->mlx_ptr == NULL)
	{
		perror("Error.\nCould not init mlx.\n");
		return (FAILURE);
	}
	d->tex = 0;
	if (ft_import_xpm_file(d, map) == FAILURE)
	{
		perror("Error.\nCould not import xpm file.\n");
		return (FAILURE);
	}
	mlx_get_screen_size(d->mlx_ptr, &d->img.width, &d->img.height);
	d->win_ptr = mlx_new_window(d->mlx_ptr, d->img.width, d->img.height,
			"CUB3D");
	if (d->win_ptr == NULL)
	{
		perror("Error.\nCould not create a new window.\n");
		return (FAILURE);
	}
	return (create_new_img(d));
}

static void	ft_clear_all(t_data *data)
{
	int	i;

	i = -1;
	if (data->img.mlx_img)
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	while (++i < 4 && data->tex != 0)
	{
		if (data->tex[i].mlx_img)
		{
			mlx_destroy_image(data->mlx_ptr, data->tex[i].mlx_img);
			data->tex[i].mlx_img = 0;
		}
	}
	free(data->tex);
	if (data->mlx_ptr != 0)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}

int	ft_mlx(t_map *map)
{
	t_data	data;

	data.img.tmap = map;
	if (ft_create_mlx_win_and_img(&data, map) != -1)
	{
		ft_setup_player(&data);
		ft_mlx_hook(&data);
		mlx_loop(data.mlx_ptr);
		if (data.img.rays != 0)
			free(data.img.rays);
	}
	ft_clear_all(&data);
	return (SUCCESS);
}
