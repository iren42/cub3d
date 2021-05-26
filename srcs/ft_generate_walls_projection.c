#include "cub3d.h"
#include <string.h>

static void	ft_calc_wall_top_bottom_pix(t_var_generate_walls_proj *var)
{
	float	perp_distance;
	float	projected_wall_height;

	perp_distance = var->ray_distance * cos(var->ray_angle
			- var->player_rotation_angle);
	projected_wall_height = (TILE_SIZE / perp_distance) *
		var->distance_proj_plane;
	var->wall_strip_height = projected_wall_height;
	var->wall_top_pixel = (WINDOW_HEIGHT / 2) - ((int)projected_wall_height / 2);
	var->wall_top_pixel = var->wall_top_pixel < 0 ? 0 : var->wall_top_pixel;
	var->wall_bottom_pixel = (WINDOW_HEIGHT / 2) + ((int)projected_wall_height / 2);
	var->wall_bottom_pixel = var->wall_bottom_pixel > WINDOW_HEIGHT ?
		WINDOW_HEIGHT : var->wall_bottom_pixel;
}

void		ft_ceiling_projection(t_data *data, int wall_top_pixel, int i)
{
	int	top_pixel;

	top_pixel = 0;
	while (top_pixel < wall_top_pixel)
	{
		ft_img_pix_put(&data->img, i, top_pixel, BLUE_PIXEL);
		top_pixel++;
	}

}
int			ft_get_pix_color(t_tex img, int x, int y)
{
	int	a;

	a = 0x0;
	if (x >= 0 && x < img.width && y >= 0 && y <= img.height)
		a = *(int*)(img.addr + (x + y * img.width) * img.bpp / 8);
	return (a);
}

void		ft_walls_projection(t_data *data, t_var_generate_walls_proj var, int i)
{
	int		tex_offset_x;
	int		tex_offset_y;
	int		j;
	int		color;

	j = var.wall_top_pixel;
	if (data->img.rays[i].was_hit_vertical)
		tex_offset_x = (int)data->img.rays[i].wall_hit_y % TILE_SIZE;
	else
		tex_offset_x = (int)data->img.rays[i].wall_hit_x % TILE_SIZE;
	while (j < var.wall_bottom_pixel)
	{
		tex_offset_y = (j - var.wall_top_pixel) * 
			((float)data->tex_ceiling.height / var.wall_strip_height);
		color = ft_get_pix_color(data->tex_ceiling, tex_offset_x, tex_offset_y);
		ft_img_pix_put(&data->img, i, j, color);
		j++;
	}
}

void		ft_floor_projection(t_data *data, int wall_bottom_pixel, int i)
{
	while (wall_bottom_pixel < WINDOW_HEIGHT)
	{
		ft_img_pix_put(&data->img, i, wall_bottom_pixel, BROWN_PIXEL);
		wall_bottom_pixel++;
	}
}

void		ft_xpm(t_data *data)
{
	int	wid;
	int hei;
	//	t_img *tex;

	char *path = "./textures/redbrick.xpm";
	data->tex_ceiling.tex_img = mlx_xpm_file_to_image(data->mlx_ptr, path, &wid, &hei);
	data->tex_ceiling.addr = mlx_get_data_addr(data->tex_ceiling.tex_img, &data->tex_ceiling.bpp,
		&data->tex_ceiling.line_len, &data->tex_ceiling.endian);
	data->tex_ceiling.height = hei;
	data->tex_ceiling.width = wid;
//	printf("wid hei from tex : %d %d\n", wid, hei);
}

void		ft_generate_walls_projection(t_data *data)
{
	int							i;
	t_var_generate_walls_proj	var;

	i = 0;
	var.distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	var.player_rotation_angle = data->img.player.rotation_angle;
	ft_xpm(data);
	while (i < NUM_RAYS)
	{
		var.ray_angle = data->img.rays[i].ray_angle;
		var.ray_distance = data->img.rays[i].distance;
		ft_calc_wall_top_bottom_pix(&var);
		ft_ceiling_projection(data, var.wall_top_pixel, i);
		ft_walls_projection(data, var, i);
/*		while (var.wall_top_pixel < var.wall_bottom_pixel)
		{
			ft_img_pix_put(&data->img, i, var.wall_top_pixel, WHITE_PIXEL);
			var.wall_top_pixel++;
		}
*/		ft_floor_projection(data, var.wall_bottom_pixel, i);
		i++;
	}
}
