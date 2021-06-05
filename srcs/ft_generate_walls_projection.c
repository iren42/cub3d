#include "cub3d.h"

static void	ft_calc_wall_top_bottom_pix(t_var_generate_walls_proj *var)
{
	float	perp_distance;
	float	proj_wall_height;

	perp_distance = var->ray_distance * cos(var->ray_angle
			- var->player_rotation_angle);
	proj_wall_height = (TILE_SIZE / perp_distance)
		* var->distance_proj_plane;
	var->wall_strip_height = proj_wall_height;
	var->wall_top_pixel = (WINDOW_HEIGHT / 2) - ((int)proj_wall_height / 2);
	if (var->wall_top_pixel < 0)
		var->wall_top_pixel = 0;
	var->wall_bottom_pixel = (WINDOW_HEIGHT / 2) + ((int)proj_wall_height / 2);
	if (var->wall_bottom_pixel > WINDOW_HEIGHT)
		var->wall_bottom_pixel = WINDOW_HEIGHT;
}

static void	ft_ceiling_projection(t_data *data, int wall_top_pixel, int i)
{
	int	top_pixel;

	top_pixel = 0;
	while (top_pixel < wall_top_pixel)
	{
		ft_img_pix_put(&data->img, i, top_pixel, BLUE_PIXEL);
		top_pixel++;
	}
}

static void	ft_floor_projection(t_data *data, int wall_bottom_pixel, int i)
{
	while (wall_bottom_pixel < WINDOW_HEIGHT)
	{
		ft_img_pix_put(&data->img, i, wall_bottom_pixel, BROWN_PIXEL);
		wall_bottom_pixel++;
	}
}

void	ft_generate_walls_projection(t_data *data)
{
	int							i;
	t_var_generate_walls_proj	var;

	i = 0;
	var.distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	var.player_rotation_angle = data->img.player.rotation_angle;
	while (i < NUM_RAYS)
	{
		var.ray_angle = data->img.rays[i].ray_angle;
		var.ray_distance = data->img.rays[i].distance;
		ft_calc_wall_top_bottom_pix(&var);
		ft_ceiling_projection(data, var.wall_top_pixel, i);
		ft_walls_projection(data, var, i);
		ft_floor_projection(data, var.wall_bottom_pixel, i);
		i++;
	}
}
