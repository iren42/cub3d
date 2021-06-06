/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:18:44 by iren              #+#    #+#             */
/*   Updated: 2021/06/06 13:48:13 by iren             ###   ########.fr       */
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
				return (SUCCESS);
		}
	}
	return (FAILURE);
}

static int	does_map_have_oao_player(char **tab, int *player_x, int *player_y)
{
	int	nb_players;
	int	i;
	int	j;

	nb_players = 0;
	i = 0;
	while (tab[i] != 0)
	{
		j = 0;
		while (tab[i][j] != '\0')
		{
			if (tab[i][j] == 'N' || tab[i][j] == 'E' || tab[i][j] == 'W'
			|| tab[i][j] == 'S')
			{
				nb_players++;
				*player_x = i;
				*player_y = j;
			}
			j++;
		}
		i++;
	}
	if (nb_players != 1)
		return (0);
	return (1);
}

static int	ft_is_map_valid(t_map *map)
{
	int	player_x;
	int	player_y;

	if (does_map_have_oao_player(map->map, &player_x, &player_y) != 1)
		return (0);
	if (!ft_is_map_closed(*map, player_x, player_y))
		return (0);
	return (1);
}

int	ft_parse_all(char *name, t_map *map)
{
	int	fd;

	fd = 0;
	if (!ft_is_filename_valid(name))
	{
		printf("Error.\nFilename invalid.\n");
		return (FAILURE);
	}
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		perror("Error.\n");
		return (FAILURE);
	}
	ft_set_tmap(fd, map);
	if (close(fd) < 0)
	{
		perror("Error.\n");
		return (FAILURE);
	}
	if (ft_is_map_valid(map) == 0)
		return (FAILURE);
	return (SUCCESS);
}
