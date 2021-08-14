/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 23:08:32 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 12:51:19 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// setup player
static int	ft_setup_player(t_data *data)
{
	// rotate player accordingly
	if (data->img.tmap->map[data->img.tmap->player_y][data->img.tmap->player_x] == 'S')
		data->img.player.rotation_angle = PI / 2; // use 'N', 'S', 'E', 'W'
	else if (data->img.tmap->map[data->img.tmap->player_y][data->img.tmap->player_x] == 'N')
		data->img.player.rotation_angle = 3 * PI / 2; // use 'N', 'S', 'E', 'W'
	else if (data->img.tmap->map[data->img.tmap->player_y][data->img.tmap->player_x] == 'W')
		data->img.player.rotation_angle = PI; // use 'N', 'S', 'E', 'W'
	else
		data->img.player.rotation_angle = 0; // use 'N', 'S', 'E', 'W'
	data->img.tmap->map[data->img.tmap->player_y][data->img.tmap->player_x] = '0';
	// player's starting position
	data->img.player.x = (TILE_SIZE * (data->img.tmap->player_x + 0.5));
	data->img.player.y = (TILE_SIZE * (data->img.tmap->player_y + 0.5));
	data->img.player.width = 5;
	data->img.player.height= 5;
	data->img.player.turn_dir = 0;
	data->img.player.walk_dir = 0;
	data->img.player.cam_dir = 0;
	data->img.player.walk_speed = 10;	// was 50
	data->img.player.turn_speed = 20 * (PI / 180); // was 45
	data->img.rays = malloc(sizeof(t_ray) * data->img.width);
	if (data->img.rays == NULL)
		return (FAILURE);
	return (SUCCESS);
}

int	ft_create_mlx_win_and_img(t_data *data, t_map *map)
{
	data->mlx_ptr = 0;
	data->win_ptr = 0;
	data->mlx_ptr = mlx_init();
	data->img.mlx_img = 0;
	if (data->mlx_ptr == NULL)
	{
		perror("Error.\nCould not init mlx.\n");
		return (FAILURE);
	}
	data->tex = 0;
	if (ft_import_xpm_file(data, map) == FAILURE)
	{
		perror("Error.\nCould not import xpm file.\n");
		return (FAILURE);
	}
	mlx_get_screen_size(data->mlx_ptr, &data->img.width, &data->img.height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->img.width, data->img.height, "CUB3D");
	if (data->win_ptr == NULL)
	{
		perror("Error.\nCould not create a new window.\n");
		return (FAILURE);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, data->img.width, data->img.height);
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

void	ft_clear_all(t_data *data)
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

int ft_mlx(t_map *map)
{
	t_data	data;
	int err;

	err = 0;
	data.img.tmap = map;
	err = ft_create_mlx_win_and_img(&data, map);
	if (err != -1)
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
