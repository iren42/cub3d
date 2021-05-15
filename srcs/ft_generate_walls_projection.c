#include "cub3d.h"

static void	ft_calc_wall_top_bottom_pix(int *wall_top_pixel,
	int *wall_bottom_pixel, t_var_generate_walls_proj var)
{
	float	perp_distance;
	float	projected_wall_height;

	perp_distance = var.ray_distance * cos(var.ray_angle
		- var.player_rotation_angle);
	projected_wall_height = (TILE_SIZE / perp_distance) *
		var.distance_proj_plane;
	*wall_top_pixel = (WINDOW_HEIGHT / 2) - ((int)projected_wall_height / 2);
	*wall_top_pixel = *wall_top_pixel < 0 ? 0 : *wall_top_pixel;
	*wall_bottom_pixel = (WINDOW_HEIGHT / 2) + ((int)projected_wall_height / 2);
	*wall_bottom_pixel = *wall_bottom_pixel > WINDOW_HEIGHT ?
		WINDOW_HEIGHT : *wall_bottom_pixel;
}

void		ft_ceiling_projection(t_img *img, int wall_top_pixel, int i)
{
	int	top_pixel;

	top_pixel = 0;
	while (top_pixel < wall_top_pixel)
	{
		ft_img_pix_put(img, i, top_pixel, BLUE_PIXEL);
		top_pixel++;
	}
}

void		ft_floor_projection(t_img *img, int wall_bottom_pixel, int i)
{
	while (wall_bottom_pixel < WINDOW_HEIGHT)
	{
		ft_img_pix_put(img, i, wall_bottom_pixel, BROWN_PIXEL);
		wall_bottom_pixel++;
	}
}

void		ft_generate_walls_projection(t_img *img)
{
	int							i;
	int							wall_top_pixel;
	int							wall_bottom_pixel;
	t_var_generate_walls_proj	var;

	i = 0;
	var.distance_proj_plane = (WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2);
	var.player_rotation_angle = img->player.rotation_angle;
	while (i < NUM_RAYS)
	{
		var.ray_angle = img->rays[i].ray_angle;
		var.ray_distance = img->rays[i].distance;
		ft_calc_wall_top_bottom_pix(&wall_top_pixel, &wall_bottom_pixel, var);
		ft_ceiling_projection(img, wall_top_pixel, i);
		while (wall_top_pixel < wall_bottom_pixel)
		{
			ft_img_pix_put(img, i, wall_top_pixel, WHITE_PIXEL);
			wall_top_pixel++;
		}
		ft_floor_projection(img, wall_bottom_pixel, i);
		i++;
	}
}
