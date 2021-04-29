#include "cub3d.h"

int	ft_render_line(t_img *img, int x0, int y0, int x1, int y1)
{
	//printf("%d\t%d\t\t%d\t%d\n", beginX, beginY, endX, endY);
	int		i;
	double	x;
	double	y;
	double	length;

	y = y1 - y0; 
	x = x1 - x0; 
	length = sqrt( x*x + y*y ); 
	x = x0; 
	y = y0; 
	while (i < length)
	{
		ft_img_pix_put(img, x, y, RED_PIXEL); 
		x += (x1 - x0) / length;
		y += (y1 - y0) / length; 
		i++;
	} 
	return (SUCCESS);
}
