/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_import_xpm_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 23:04:29 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 12:52:54 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_import_xpm_file(t_data *data, t_map *map)
{
	int		wid;
	int		hei;
	int		i;
	char	*filename;

	i = -1;
	wid = 0;
	hei = 0;
	data->tex = malloc(sizeof(t_img) * 4);
	if (data->tex != NULL)
	{
		while (++i < 4)
			data->tex[i].mlx_img = 0;
		i = -1;
		while (++i < 4)
		{
			filename = map->texture[i];
			data->tex[i].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, filename, &wid, &hei);
			if (data->tex[i].mlx_img == NULL)
				return (FAILURE);
			data->tex[i].addr = mlx_get_data_addr(data->tex[i].mlx_img, &data->tex[i].bpp,
					&data->tex[i].line_len, &data->tex[i].endian);
			data->tex[i].height = hei;
			data->tex[i].width = wid;
		}
		return (SUCCESS);
	}
	return (FAILURE);
}
