/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:18:44 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 08:50:32 by iren             ###   ########.fr       */
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
		//		printf("rows cols %d %d\n", tmap->rows, tmap->cols);
		while (++i < tmap->rows)
		{
			j = -1;
			while (++j < tmap->cols)
			{
				if (tmap->map[i][j] == 'N' || tmap->map[i][j] == 'E'
						|| tmap->map[i][j] == 'W' || tmap->map[i][j] == 'S')
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
		perror("Error.\nMap does not have 1 player.\n");
		return (-1);
	}
	if (!ft_is_map_closed(map, player_x, player_y))
	{
		perror("Error.\nMap walls are not closed.\n");
		return (-1);
	}
	map->player_x = player_x;
	map->player_y = player_y;
	return (1);
}

static int	ft_open_close_fd(char *name, int *fd, t_map *map)
{
	*fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror("Error.\nFile could not be opened.\n");
		return (-1);
	}
	if (ft_set_tmap(*fd, map) == -1)
	{
		return (-1);
	}
	if (close(*fd) < 0)
	{
		perror("Error.\nFile could not close.\n");
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
		perror("Error.\nFilename invalid.\n");
		return (FAILURE);
	}
	if (ft_open_close_fd(name, &fd, tmap) == -1)
		return (FAILURE);
	if (ft_is_map_valid(tmap) == -1)
	{
		perror("Error.\nMap is not valid.\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
