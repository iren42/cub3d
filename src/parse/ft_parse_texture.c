/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 02:30:47 by iren              #+#    #+#             */
/*   Updated: 2021/08/15 07:27:39 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_pathname(char *line)
{
	int		i;
	int		a;
	char	*name;

	i = 0;
	a = 0;
	name = 0;
	name = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (name != NULL)
	{
		while (line[i])
			name[a++] = line[i++];
		name[a] = '\0';
	}
	return (name);
}

static char	*get_texture_path(char *line, char *map_tex)
{
	char	*path_texture;
	int		len;
	int		i;

	path_texture = 0;
	if (!ft_isspace(line[2]))
		return (0);
	i = ft_skip_spaces(line, 2);
	path_texture = get_pathname(&line[i]);
	if (path_texture != NULL)
	{
		len = ft_strlen(path_texture);
		map_tex = malloc(sizeof(char) * (len + 1));
		if (map_tex != NULL)
			ft_memmove(map_tex, path_texture, len + 1);
	}
	free(path_texture);
	return (map_tex);
}

void	ft_parse_texture(char *line, t_map *map)
{
	if (ft_strncmp(line, "NO", 2) == 0 && map->texture[no] == 0)
		map->texture[no] = get_texture_path(line, map->texture[no]);
	else if (ft_strncmp(line, "SO", 2) == 0 && map->texture[so] == 0)
		map->texture[so] = get_texture_path(line, map->texture[so]);
	else if (ft_strncmp(line, "WE", 2) == 0 && map->texture[we] == 0)
		map->texture[we] = get_texture_path(line, map->texture[we]);
	else if (ft_strncmp(line, "EA", 2) == 0 && map->texture[ea] == 0)
		map->texture[ea] = get_texture_path(line, map->texture[ea]);
	else if (line[0] == 'F' || line[0] == 'C' || line[0] == '\0')
		;
	else
	{
		ft_putstr_fd("Error\nTake a look on textures in file descriptor.\n", 2);
		map->error = -1;
	}
}
