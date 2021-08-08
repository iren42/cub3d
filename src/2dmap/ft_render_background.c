#include "cub3d.h"

void	ft_render_background(t_data *data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->img.height)
	{
		j = 0;
		while (j < data->img.width)
		{
			ft_img_pix_put(&data->img, j++, i, color);
		}
		++i;
	}
}
