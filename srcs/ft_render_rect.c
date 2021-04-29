#include "cub3d.h"

int ft_render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			ft_img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}
