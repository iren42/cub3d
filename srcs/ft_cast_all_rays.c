#include "cub3d.h"
#include <limits.h>

float	ft_normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI * angle;
	return (angle);
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	return (sqrt(x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	ft_cast_ray(t_ray *rays, float ray_angle, int strip_id, t_player player)
{
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	int		is_ray_facing_left;
	int		is_ray_facing_right;

	ray_angle = ft_normalize_angle(ray_angle);
	is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
	is_ray_facing_up = !is_ray_facing_down;
	is_ray_facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	is_ray_facing_left = !is_ray_facing_right;

	float xintercept;
	float yintercept;
	float xstep;
	float ystep;

	// HORIZONTAL
	int found_hor_wall_hit = 0;
	float hor_wall_hit_x = 0;
	float hor_wall_hit_y = 0;
	int	hor_wall_content = 0;

	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	yintercept += is_ray_facing_down ? TILE_SIZE : 0;

	xintercept = player.x + (yintercept - player.y) / tan(ray_angle);

	ystep = TILE_SIZE;
	ystep *= is_ray_facing_up ? -1 : 1;

	xstep = TILE_SIZE / tan(ray_angle);
	xstep *= (is_ray_facing_left && xstep > 0) ? -1 : 1;
	xstep *= (is_ray_facing_right && xstep < 0) ? -1 : 1;

	float	next_hor_touch_x = xintercept;
	float	next_hor_touch_y = yintercept;

	while (next_hor_touch_x >= 0 && next_hor_touch_x <= WINDOW_WIDTH
			&& next_hor_touch_y >= 0 && next_hor_touch_y <= WINDOW_HEIGHT)
	{
		float	x_tocheck = next_hor_touch_x;
		float	y_tocheck = next_hor_touch_y + (is_ray_facing_up ? -1 : 0);

		if (ft_map_has_wall_at(x_tocheck, y_tocheck))
		{
			hor_wall_hit_x = next_hor_touch_x;
			hor_wall_hit_y = next_hor_touch_y;
			hor_wall_content = 
			map[(int)floor(y_tocheck / TILE_SIZE)][(int)floor(x_tocheck / TILE_SIZE)];
			found_hor_wall_hit = 1;
			break;
		}
		else
		{
			next_hor_touch_x += xstep;
			next_hor_touch_y += ystep;
		}

	}
	// VERTICAL
	int found_vert_wall_hit = 0;
	float vert_wall_hit_x = 0;
	float vert_wall_hit_y = 0;
	int	vert_wall_content = 0;

	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	xintercept += is_ray_facing_right ? TILE_SIZE : 0;

	yintercept = player.y + (xintercept - player.x) * tan(ray_angle);

	xstep = TILE_SIZE;
	xstep *= is_ray_facing_left ? -1 : 1;

	ystep = TILE_SIZE * tan(ray_angle);
	ystep *= (is_ray_facing_up && ystep > 0) ? -1 : 1;
	ystep *= (is_ray_facing_down && ystep < 0) ? -1 : 1;

	float	next_vert_touch_x = xintercept;
	float	next_vert_touch_y = yintercept;

	while (next_vert_touch_x >= 0 && next_vert_touch_x <= WINDOW_WIDTH
			&& next_vert_touch_y >= 0 && next_vert_touch_y <= WINDOW_HEIGHT)
	{
		float	x_tocheck = next_vert_touch_x + (is_ray_facing_left ? -1: 0);
		float	y_tocheck = next_vert_touch_y;

		if (ft_map_has_wall_at(x_tocheck, y_tocheck))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = 
				map[(int)floor(y_tocheck / TILE_SIZE)][(int)floor(x_tocheck / TILE_SIZE)];
			found_vert_wall_hit = 1;
			break;
		}
		else
		{
			next_vert_touch_x += xstep;
			next_vert_touch_y += ystep;
		}
	}

	float hor_hit_distance = found_hor_wall_hit
		? distance_between_points(player.x, player.y, hor_wall_hit_x, hor_wall_hit_y) 
		: INT_MAX; 
	float vert_hit_distance = found_vert_wall_hit 
		? distance_between_points(player.x, player.y, vert_wall_hit_x, vert_wall_hit_y) 
		: INT_MAX;
	if  (vert_hit_distance < hor_hit_distance)
	{
		rays[strip_id].distance = vert_hit_distance;
		rays[strip_id].wall_hit_x = vert_wall_hit_x;
		rays[strip_id].wall_hit_y = vert_wall_hit_y;
		rays[strip_id].wall_hit_content = vert_wall_content;
		rays[strip_id].was_hit_vertical = 1;
	}
	else
	{
		rays[strip_id].distance = hor_hit_distance;
		rays[strip_id].wall_hit_x = hor_wall_hit_x;
		rays[strip_id].wall_hit_y = hor_wall_hit_y;
		rays[strip_id].wall_hit_content = hor_wall_content;
		rays[strip_id].was_hit_vertical = 0;


	}
	rays[strip_id].ray_angle = ray_angle;
	rays[strip_id].is_ray_facing_up = is_ray_facing_up;
	rays[strip_id].is_ray_facing_down = is_ray_facing_down;
	rays[strip_id].is_ray_facing_left = is_ray_facing_left;
	rays[strip_id].is_ray_facing_right = is_ray_facing_right;
}

void	ft_cast_all_rays(t_player player, t_ray *rays)
{
	float	ray_angle;
	int		i;

	i = 0;
	if (rays != NULL)
	{
		ray_angle = player.rotation_angle - (FOV_ANGLE / 2);
		while (i < NUM_RAYS)
		{
			ft_cast_ray(rays, ray_angle, i, player);
	//		rays[i].ray_angle = ray_angle;
			ray_angle += FOV_ANGLE / NUM_RAYS;
			i++;
		}
		printf("rays were casted***\n");
	}
}
