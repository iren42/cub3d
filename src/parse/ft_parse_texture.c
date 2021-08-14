/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 02:30:47 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 14:32:35 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*ft_get_pathname(char *line)
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
		while (line[i]
			&& (line[i] != ' ' || (line[i - 1] == '\\' && line[i] == ' ')))
			name[a++] = line[i++];
		name[a] = '\0';
	}
	return (name);
}

static char	*ft_get_texture_path(char *line, char *map_tex)
{
	char	*path_texture;
	int		len;
	int		i;

	path_texture = 0;
	i = ft_skip_spaces(line, 2);
	path_texture = ft_get_pathname(&line[i]);
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
	if (ft_strncmp(line, "NO ", 3) == 0 && map->texture[no] == 0)
		map->texture[no] = ft_get_texture_path(line, map->texture[no]);
	else if (ft_strncmp(line, "SO ", 3) == 0 && map->texture[so] == 0)
		map->texture[so] = ft_get_texture_path(line, map->texture[so]);
	else if (ft_strncmp(line, "WE ", 3) == 0 && map->texture[we] == 0)
		map->texture[we] = ft_get_texture_path(line, map->texture[we]);
	else if (ft_strncmp(line, "EA ", 3) == 0 && map->texture[ea] == 0)
		map->texture[ea] = ft_get_texture_path(line, map->texture[ea]);
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0
		|| line[0] == '\0')
		;
	else
	{
		perror("Error.\nTake a look on textures in file descriptor.\n");
		map->error = -1;
	}
}
