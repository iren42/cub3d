#include "cub3d.h"

int	ft_get_pix_color(t_img *img, int x, int y)
{
	int	a;

	a = 0x0;
	if (x >= 0 && x < img->width && y >= 0 && y <= img->height)
		a = *(int*)(img->addr + (x + y * img->width) * img->bpp / 8);
	return (a);
}

// returns a texture sample
static t_img	*ft_get_tex_seen(t_data *data, int i)
{
	if (!data->img.rays[i].is_ray_facing_down && !data->img.rays[i].was_hit_vertical)
		return (&data->tex[So]);
	else if (data->img.rays[i].is_ray_facing_down && !data->img.rays[i].was_hit_vertical)
		return (&data->tex[No]);
	else if (!data->img.rays[i].is_ray_facing_right && data->img.rays[i].was_hit_vertical)
		return (&data->tex[Ea]);
	else 
		return (&data->tex[We]);
}

void	ft_walls_projection(t_data *data, t_var_generate_walls_proj var, int i)
{
	int		tex_offset_x;
	int		tex_offset_y;
	int		j;
	int		distance_from_top;
	t_img	*tex_seen;

	j = var.wall_top_pixel;
	if (data->img.rays[i].was_hit_vertical)
		tex_offset_x = (int)data->img.rays[i].wall_hit_y % TILE_SIZE;
	else
		tex_offset_x = (int)data->img.rays[i].wall_hit_x % TILE_SIZE;
	while (j < var.wall_bottom_pixel)
	{
		distance_from_top = j + (var.wall_strip_height / 2) - (data->img.height / 2);
		 tex_seen = ft_get_tex_seen(data, i);
		 tex_offset_y = distance_from_top * 
		((float)tex_seen->height / var.wall_strip_height);
		if (ft_get_pix_color(&data->img, i, j) != ft_get_pix_color(tex_seen, tex_offset_x, tex_offset_y))
		ft_img_pix_put(&data->img, i, j, 
				ft_get_pix_color(tex_seen, tex_offset_x, tex_offset_y));
		j++;
	}
}
