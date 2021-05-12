/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:18:44 by iren              #+#    #+#             */
/*   Updated: 2021/04/18 16:40:13 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "cub3d.h"

int	ft_check_name(char *name)
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

int	ft_read_map(int fd, t_map *map)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strchr("RNOSWEAFC", line[0]) != NULL) // if the 1st char of line is one of R, N or \0, etc then do
		{
			printf("%s\n", line);
			ft_parse_R(line, map);
			ft_parse_texture(line, map);
	//		ft_parse_color(line, map);
		}
	}
	free(line);
	return (SUCCESS);
}

int ft_parse_map(char *name, t_map *map)
{
	int fd;

	fd = 0;
	if (!ft_check_name(name))
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
	ft_read_map(fd, map);
	if (close(fd) < 0)
	{
		perror("Error.\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
