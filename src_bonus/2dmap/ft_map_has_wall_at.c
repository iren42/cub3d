/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_has_wall_at.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 20:23:52 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 16:56:32 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_map_has_wall_at(t_data *data, float x, float y)
{
	int	map_grid_index_x;
	int	map_grid_index_y;

	if (x < 0 || x > data->img.width || y < 0 || y > data->img.height)
		return (1);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
	if (map_grid_index_x >= data->img.tmap->cols
		|| map_grid_index_y >= data->img.tmap->rows)
		return (1);
	return (data->img.tmap->map[map_grid_index_y][map_grid_index_x] != '0');
}
