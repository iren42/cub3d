/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:18:44 by iren              #+#    #+#             */
/*   Updated: 2021/08/15 07:24:25 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

static int	ft_is_filename_valid(char *name)
{
	char	*str;

	str = NULL;
	if (name != NULL)
	{
		str = ft_strnstr(name, ".", ft_strlen(name));
		if (str != NULL)
		{
			if (ft_strncmp(str, ".cub", 5) == 0)
				return (1);
		}
	}
	return (-1);
}

static int	is_nb_of_players(t_map *tmap, int *player_x, int *player_y)
{
	int	nb_players;
	int	i;
	int	j;

	nb_players = 0;
	if (tmap->map != 0)
	{
		i = -1;
		while (++i < tmap->rows)
		{
			j = -1;
			while (++j < tmap->cols)
			{
				if (ft_is_player_char(tmap->map[i][j]))
				{
					nb_players++;
					*player_x = j;
					*player_y = i;
				}
			}
		}
	}
	if (nb_players != 1)
		return (-1);
	return (1);
}

static int	ft_is_map_valid(t_map *map)
{
	int	player_x;
	int	player_y;

	if (is_nb_of_players(map, &player_x, &player_y) != 1)
	{
		ft_putstr_fd("Error\nMap does not have 1 player.\n", 2);
		return (-1);
	}
	if (ft_find_proh_zero(map, player_x, player_y))
	{
		ft_putstr_fd("Error\nMap walls are not closed.\n", 2);
		return (-1);
	}
	map->px = player_x;
	map->py = player_y;
	return (1);
}

static int	ft_open_close_fd(char *name, int *fd, t_map *map)
{
	*fd = open(name, O_RDONLY);
	if (*fd < 0)
	{
		ft_putstr_fd("Error\nFile could not be opened.\n", 2);
		return (-1);
	}
	if (ft_set_tmap(*fd, map) == -1)
	{
		ft_putstr_fd("Error\nIn ft_parse_all.c: ft_set_tmap failed.\n", 2);
		return (-1);
	}
	if (close(*fd) < 0)
	{
		ft_putstr_fd("Error\nFile could not close.\n", 2);
		return (-1);
	}
	return (1);
}

int	ft_parse_all(char *name, t_map *tmap)
{
	int	fd;

	fd = 0;
	if (ft_is_filename_valid(name) == -1)
	{
		ft_putstr_fd("Error\nFilename invalid.\n", 2);
		return (FAILURE);
	}
	if (ft_open_close_fd(name, &fd, tmap) == -1)
		return (FAILURE);
	if (ft_is_map_valid(tmap) == -1)
	{
		ft_putstr_fd("Error\nMap is not valid.\n", 2);
		return (FAILURE);
	}
	return (SUCCESS);
}
