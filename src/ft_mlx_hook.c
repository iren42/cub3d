/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:31:41 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 14:00:41 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/X.h>
#include <X11/keysym.h>

static int	main_loop(t_data *data)
{
	ft_refresh_img(data);
	return (0);
}

static void	update_player_values(t_data *data, t_player *p)
{
	float	new_px;
	float	new_py;

	p->rotation_angle += p->turn_dir * p->turn_speed;
	if (p->turn_dir != 0 || p->walk_dir != 0)
	{
		new_px = p->x + cos(p->rotation_angle) * (p->walk_dir * p->walk_speed);
		new_py = p->y + sin(p->rotation_angle) * (p->walk_dir * p->walk_speed);
	}
	else
	{
		new_px = p->x + cos(p->rotation_angle + (PI / 2)
				* p->cam_dir) * p->walk_speed;
		new_py = p->y + sin(p->rotation_angle + (PI / 2)
				* p->cam_dir) * p->walk_speed;
	}
	if (!ft_map_has_wall_at(data, new_px, new_py))
	{
		p->x = new_px;
		p->y = new_py;
	}
}

static int	handle_keyrelease(int keysym, t_data *data)
{
	if (keysym == XK_w || keysym == XK_s)
	{
		data->img.player.walk_dir = 0;
	}
	else if (keysym == XK_Right || keysym == XK_Left)
	{
		data->img.player.turn_dir = 0;
	}
	else if (keysym == XK_a || keysym == XK_d)
	{
		data->img.player.cam_dir = 0;
	}
	return (0);
}

static int	handle_keypress(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (key == XK_a || key == XK_d || key == XK_w || key == XK_s
		|| key == XK_Right || key == XK_Left)
	{
		if (key == XK_a)
			data->img.player.cam_dir = -1;
		else if (key == XK_d)
			data->img.player.cam_dir = +1;
		else if (key == XK_w)
			data->img.player.walk_dir = +1;
		else if (key == XK_s)
			data->img.player.walk_dir = -1;
		else if (key == XK_Right)
			data->img.player.turn_dir = +1;
		else
			data->img.player.turn_dir = -1;
		update_player_values(data, &(data->img.player));
	}
	return (0);
}

void	ft_mlx_hook(t_data *data)
{
	if (data != NULL)
	{
		mlx_loop_hook(data->mlx_ptr, &main_loop, data);
		mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
		mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask,
			&handle_keyrelease, data);
		mlx_hook(data->win_ptr, 33, 1L << 2, &ft_close, data);
	}
}
