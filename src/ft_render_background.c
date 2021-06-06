#include "cub3d.h"

void	ft_render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			ft_img_pix_put(img, j++, i, color);
		}
		++i;
	}
}
