#include "cub3d.h"

void	ft_calculate_hor_step(float *xstep, float *ystep,
	t_ray ray, float ray_angle)
{
	*ystep = TILE_SIZE;
	*ystep *= ray.is_ray_facing_down ? 1 : -1;
	*xstep = TILE_SIZE / tan(ray_angle);
	*xstep *= (!ray.is_ray_facing_right && *xstep > 0) ? -1 : 1;
	*xstep *= (ray.is_ray_facing_right && *xstep < 0) ? -1 : 1;
}

void	ft_calculate_ver_step(float *xstep, float *ystep,
	t_ray ray, float ray_angle)
{
	*xstep = TILE_SIZE;
	*xstep *= ray.is_ray_facing_right ? 1 : -1;
	*ystep = TILE_SIZE * tan(ray_angle);
	*ystep *= (!ray.is_ray_facing_down && *ystep > 0) ? -1 : 1;
	*ystep *= (ray.is_ray_facing_down && *ystep < 0) ? -1 : 1;
}
