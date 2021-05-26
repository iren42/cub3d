#include "cub3d.h"

void		ft_import_xpm_file(t_data *data, t_map map)
{
	int	wid;
	int hei;
	int	i;
	//	t_img *tex;

	char *filename;
	i = 0;
	data->tex = malloc(sizeof(t_tex) * 4); // 5 for sprite
	if (data->tex != NULL)
		while (i < 4)
		{
			filename = map.texture[i]; // TODO: verify if mlx xpm file to image worked
			data->tex[i].tex_img = mlx_xpm_file_to_image(data->mlx_ptr, filename, &wid, &hei);
			data->tex[i].addr = mlx_get_data_addr(data->tex[i].tex_img, &data->tex[i].bpp,
					&data->tex[i].line_len, &data->tex[i].endian);
			data->tex[i].height = hei;
			data->tex[i].width = wid;
			i++;
			printf("tex wid hei : %d %d filename %s\n", wid, hei, filename);
		}
}
