#include "cub3d.h"
#include <X11/X.h>
#include <X11/keysym.h>
int	ft_handle_no_event(void *data)
{
	/* This function needs to exist, but it is useless for the moment */
	(void)data;
	return (0);
}

void	ft_update_player_s_values(t_data *data, t_player *p)
{
	float	move_step;
	float	new_player_x;
	float	new_player_y;

	p->rotation_angle += p->turn_dir * p->turn_speed;
	move_step = p->walk_dir * p->walk_speed;
	new_player_x = p->x + cos(p->rotation_angle) * move_step;
	new_player_y = p->y + sin(p->rotation_angle) * move_step;
	if (!ft_map_has_wall_at(new_player_x, new_player_y))
	{
		p->x = new_player_x;
		p->y = new_player_y;
	}
}

int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_W || keysym == XK_w)
	{
		data->img.player.walk_dir = 0;
	}
	if (keysym == XK_S || keysym == XK_s)
	{
		data->img.player.walk_dir = 0;
	}
	if (keysym == XK_d || keysym == XK_D) // right
	{
		data->img.player.turn_dir = 0;
	}
	if (keysym == XK_A || keysym == XK_a) // left
	{
		data->img.player.turn_dir = 0;
	}
	return (0);
}


int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (keysym == XK_W || keysym == XK_w)
	{
		data->img.player.walk_dir = +1;
		// refresh image
		ft_update_player_s_values(data, &(data->img.player));
		ft_refresh_img(data);
	}
	if (keysym == XK_S || keysym == XK_s)
	{
		data->img.player.walk_dir = -1;
		// refresh image
		ft_update_player_s_values(data, &(data->img.player));
		ft_refresh_img(data);
	}
	if (keysym == XK_d || keysym == XK_D) // right
	{
		data->img.player.turn_dir = +1;
		// refresh image
		ft_update_player_s_values(data, &(data->img.player));
		ft_refresh_img(data);

	}
	if (keysym == XK_A || keysym == XK_a)
	{
		data->img.player.turn_dir = -1;
		// refresh image
		ft_update_player_s_values(data, &(data->img.player));
		ft_refresh_img(data);
	}
	return (0);
}
void	ft_mlx_hook(t_data *data)
{
	mlx_loop_hook(data->mlx_ptr, &ft_handle_no_event, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, data);
	mlx_hook(data->win_ptr, 33, 1L<<2, &ft_close, data);
}

