#include "cub3d.h"

static void	ft_calc_wall_top_bottom_pix(t_data *data, t_var_generate_walls_proj *var)
{
	float	perp_distance;
	float	proj_wall_height;

	perp_distance = var->ray_distance * cos(var->ray_angle
			- var->player_rotation_angle);
	proj_wall_height = (TILE_SIZE / perp_distance)
		* var->distance_proj_plane;
	if (perp_distance == 0)
		proj_wall_height = data->img.height;
	var->wall_strip_height = proj_wall_height;
	var->wall_top_pixel = (data->img.height / 2) - ((int)proj_wall_height / 2);
//	printf("var wtp %d %d %f\n", var->wall_top_pixel, data->img.height, proj_wall_height);
	if (var->wall_top_pixel < 0)
		var->wall_top_pixel = 0;
	var->wall_bottom_pixel = (data->img.height / 2) + ((int)proj_wall_height / 2);
	if (var->wall_bottom_pixel > data->img.height)
		var->wall_bottom_pixel = data->img.height;
}

static void	ft_ceiling_projection(t_data *data, int wall_top_pixel, int i)
{
	int	top_pixel;

	top_pixel = 0;
	if (wall_top_pixel)
	while (top_pixel < wall_top_pixel)
	{
		if (ft_get_pix_color(data->img, i, top_pixel) != data->img.tmap->ceiling)
			ft_img_pix_put(&data->img, i, top_pixel, data->img.tmap->ceiling);
		top_pixel++;
	}
}

static void	ft_floor_projection(t_data *data, int wall_bottom_pixel, int i)
{
	while (wall_bottom_pixel < data->img.height)
	{
		if (ft_get_pix_color(data->img, i, wall_bottom_pixel) != data->img.tmap->floor)
			ft_img_pix_put(&data->img, i, wall_bottom_pixel, data->img.tmap->floor);
		wall_bottom_pixel++;
	}
}

void	ft_generate_walls_projection(t_data *data)
{
	int							i;
	t_var_generate_walls_proj	var;

	i = 0;
	var.distance_proj_plane = (data->img.width / 2) / tan(FOV_ANGLE / 2);
	var.player_rotation_angle = data->img.player.rotation_angle;
	while (i < data->img.width)
	{
		var.ray_angle = data->img.rays[i].ray_angle;
		var.ray_distance = data->img.rays[i].distance;
		ft_calc_wall_top_bottom_pix(data, &var);
		ft_ceiling_projection(data, var.wall_top_pixel, i);
		ft_walls_projection(data, var, i);
		ft_floor_projection(data, var.wall_bottom_pixel, i);
		i++;
	}
}
