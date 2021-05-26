/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 02:30:47 by iren              #+#    #+#             */
/*   Updated: 2021/04/19 14:20:06 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// To allow spaces after the path texture in the file description
char	*ft_get_pathname(char *line)
{
	int		i;
	int		a;
	char	*name;

	i = 0;
	a = 0;
	name = NULL;
	name = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (name != NULL)
	{
		while (line[i] && (line[i] != ' ' || (line[i - 1] == '\\' && line[i] == ' ')))
			name[a++] = line[i++];
		name[a] = '\0';
	}
	return (name);
}

// clean the pathname
char	*ft_get_texture_path(char *line, char *map_tex)
{
	char	*path_texture;
	int		len;
	int		i;

	path_texture = NULL;
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
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		map->texture[No] = ft_get_texture_path(line, map->texture[No]);

	printf("No %s\n", map->texture[No]);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
		map->texture[So] = ft_get_texture_path(line, map->texture[So]);
	if (ft_strncmp(line, "WE ", 3) == 0)
		map->texture[We] = ft_get_texture_path(line, map->texture[We]);
	if (ft_strncmp(line, "EA ", 3) == 0)
		map->texture[Ea] = ft_get_texture_path(line, map->texture[Ea]);

}
