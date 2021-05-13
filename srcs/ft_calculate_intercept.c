#include "cub3d.h"

void	ft_calculate_hor_intercept(t_var_cast_ray *var, t_ray ray, t_player player)
{
	var->yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	var->yintercept += ray.is_ray_facing_down ? TILE_SIZE : 0;
	var->xintercept = player.x + (var->yintercept - player.y) / tan(ray.ray_angle);
}

void	ft_calculate_ver_intercept(t_var_cast_ray *var, t_ray ray, t_player player)
{
	var->xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	var->xintercept += ray.is_ray_facing_right ? TILE_SIZE : 0;
	var->yintercept = player.y + (var->xintercept - player.x) * tan(ray.ray_angle);
}
