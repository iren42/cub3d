/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_import_xpm_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 23:04:29 by iren              #+#    #+#             */
/*   Updated: 2021/08/11 23:04:39 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_import_xpm_file(t_data *data, t_map *map)
{
	int	wid;
	int hei;
	int	i;

	char *filename;
	i = 0;
	data->tex = malloc(sizeof(t_img) * 4);
	if (data->tex != NULL)
		while (i < 4)
		{
			filename = map->texture[i]; // TODO: verify if mlx xpm file to image worked
			data->tex[i].mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, filename, &wid, &hei);
			data->tex[i].addr = mlx_get_data_addr(data->tex[i].mlx_img, &data->tex[i].bpp,
					&data->tex[i].line_len, &data->tex[i].endian);
			data->tex[i].height = hei;
			data->tex[i].width = wid;
			i++;
		//	free(filename);
	//		printf("tex wid hei : %d %d filename %s\n", wid, hei, filename);
		}
}
