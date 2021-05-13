#include "cub3d.h"
#include <limits.h>

static float	ft_distance_between_pts(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void			ft_fill_ray_data(t_ray *ray, t_var_cast_ray var, t_player p)
{
	float hor_hit_distance;
	float ver_hit_distance;

	hor_hit_distance = var.found_hor_wall_hit
		? ft_distance_between_pts(p.x, p.y,
				var.hor_wall_hit_x, var.hor_wall_hit_y) : INT_MAX;
	ver_hit_distance = var.found_ver_wall_hit
		? ft_distance_between_pts(p.x, p.y,
				var.ver_wall_hit_x, var.ver_wall_hit_y) : INT_MAX;
	if (ver_hit_distance < hor_hit_distance)
	{
		ray->distance = ver_hit_distance;
		ray->wall_hit_x = var.ver_wall_hit_x;
		ray->wall_hit_y = var.ver_wall_hit_y;
		ray->wall_hit_content = var.ver_wall_content;
		ray->was_hit_vertical = 1;
	}
	else
	{
		ray->distance = hor_hit_distance;
		ray->wall_hit_x = var.hor_wall_hit_x;
		ray->wall_hit_y = var.hor_wall_hit_y;
		ray->wall_hit_content = var.hor_wall_content;
		ray->was_hit_vertical = 0;
	}
}
