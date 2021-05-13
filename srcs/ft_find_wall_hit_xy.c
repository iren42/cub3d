#include "cub3d.h"

void	ft_find_hor_wall_hit_xy(t_var_cast_ray *var, t_ray *ray)
{
	float next_hor_touch_x = var->xintercept;
    float next_hor_touch_y = var->yintercept;

    while (next_hor_touch_x >= 0 && next_hor_touch_x <= WINDOW_WIDTH
		&& next_hor_touch_y >= 0 && next_hor_touch_y <= WINDOW_HEIGHT) {
        float xToCheck = next_hor_touch_x;
        float yToCheck = next_hor_touch_y + (ray->is_ray_facing_down ? 0 : -1);
        
        if (ft_map_has_wall_at(xToCheck, yToCheck)) {
            // found a wall hit
            var->hor_wall_hit_x = next_hor_touch_x;
            var->hor_wall_hit_y = next_hor_touch_y;
            var->hor_wall_content = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            var->found_hor_wall_hit = 1;
            break;
        } else {
            next_hor_touch_x += var->xstep;
            next_hor_touch_y += var->ystep;
        }
    }
}

void	ft_find_ver_wall_hit_xy(t_var_cast_ray *var, t_ray *ray)
{
	float next_ver_touch_x = var->xintercept;
    float next_ver_touch_y = var->yintercept;

    while (next_ver_touch_x >= 0 && next_ver_touch_x <= WINDOW_WIDTH
		&& next_ver_touch_y >= 0 && next_ver_touch_y <= WINDOW_HEIGHT) {
        float xToCheck = next_ver_touch_x + (ray->is_ray_facing_right ? 0 : -1);
        float yToCheck = next_ver_touch_y;
        
        if (ft_map_has_wall_at(xToCheck, yToCheck)) {
            // found a wall hit
            var->ver_wall_hit_x = next_ver_touch_x;
            var->ver_wall_hit_y = next_ver_touch_y;
            var->ver_wall_content = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            var->found_ver_wall_hit = 1;
            break;
        } else {
            next_ver_touch_x += var->xstep;
            next_ver_touch_y += var->ystep;
        }
    }
}
