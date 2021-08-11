/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:31:41 by iren              #+#    #+#             */
/*   Updated: 2021/08/11 15:31:42 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <X11/X.h>
#include <X11/keysym.h>

static int	ft_main_loop(t_data *data)
{
	ft_refresh_img(data);
	return (0);
}

static void	ft_update_player_s_values(t_data *data, t_player *p)
{
	float	move_step;
	float	side_step;
	float	new_player_x;
	float	new_player_y;

	p->rotation_angle += p->turn_dir * p->turn_speed; 
	move_step = (p->walk_dir) * p->walk_speed;
	//	printf("ro angle %f PI %f %f %f\n", p->rotation_angle, PI / 2, PI, 3 * PI / 2);
	if (p->turn_dir != 0 || p->walk_dir != 0) /// move front back and turn left right
	{
		new_player_x = p->x + cos(p->rotation_angle) * move_step;
		new_player_y = p->y + sin(p->rotation_angle) * move_step;
	}
	else // move left right
	{
		new_player_x = p->x + cos(p->rotation_angle + (PI / 2) * p->cam_dir) * p->walk_speed;
		new_player_y = p->y + sin(p->rotation_angle + (PI / 2) * p->cam_dir) * p->walk_speed;
	}
	if (!ft_map_has_wall_at(data, new_player_x, new_player_y))
	{
		p->x = new_player_x;
		p->y = new_player_y;
	}
}

int	handle_keyrelease(int keysym, t_data *data)
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


int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (keysym == XK_a) // move left
	{
		data->img.player.cam_dir = -1;
		//		printf("cam dir %d\n", data->img.player.cam_dir);
		ft_update_player_s_values(data, &(data->img.player));
	}
	else if (keysym == XK_d) // move right
	{
		data->img.player.cam_dir = +1;
		ft_update_player_s_values(data, &(data->img.player));
	}
	else if (keysym == XK_w) // move front
	{
		data->img.player.walk_dir = +1;
		//		printf("walk dir %d\n", data->img.player.walk_dir);
		ft_update_player_s_values(data, &(data->img.player));
	}
	else if (keysym == XK_s) // move back
	{
		data->img.player.walk_dir = -1;
		ft_update_player_s_values(data, &(data->img.player));
	}
	else if (keysym == XK_Right) // look right
	{
		data->img.player.turn_dir = +1;
		ft_update_player_s_values(data, &(data->img.player));

	}
	else if (keysym == XK_Left) // look left
	{
		data->img.player.turn_dir = -1;
		ft_update_player_s_values(data, &(data->img.player));
	}
	return (0);
}

void	ft_mlx_hook(t_data *data)
{
	if (data != NULL)
	{
		mlx_loop_hook(data->mlx_ptr, &ft_main_loop, data);
		mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &handle_keypress, data);
		mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, data);
		mlx_hook(data->win_ptr, 33, 1L<<2, &ft_close, data);
	}
}

