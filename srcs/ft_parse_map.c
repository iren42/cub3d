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
/*
void	ft_display(t_map map)
{
	int tab;

	tab = map.map;
	while (tab[i])
	{
	
	}

}
*/
int	ft_convert_map_lst_to_array(t_list *l, t_map *map, int rows, int cols)
{
	int i;
	int lstsize;

	lstsize = ft_lstsize(l);
	map->map = malloc(sizeof(char*) * (rows + 1));
	if (map->map == NULL)
		return (FAILURE);
	while (l)
	{
		map->map[i] = ft_strdup(l->content);
		printf("%s\n", map->map[i]);
		l = l->next;
		i++;
	}
	map->map[i] = 0;
	return (SUCCESS);
}

void	affiche_str(void *c)
{
	printf("line saved : %s\n", (char*)c);
}

void	affiche_list(t_list *l)
{
	printf("\nLIST BEGIN-----\n");
	if (l != 0)
		ft_lstiter(l, &affiche_str);
	printf("END-----\n");
}

void	ft_free_lst(void *f)
{
	free(f);
}

int	ft_is_map_description(char *line, int *map_num_cols)
{
	int i;

	i = 0;
	if (line[0] == '\0')
		return (0);
	while (line[i])
	{
		if (ft_strchr(" 210NWES", line[i]) != NULL)
			i++;
		else
			return (0);
	}
	if (i > *map_num_cols)
		*map_num_cols = i;
	return (1);
}

int	ft_read_map(int fd, t_map *map)
{
	int		ret;
	char	*line;
	int		map_num_rows;
	int		map_num_cols;
	t_list	*lst;

	map_num_rows = 0;
	map_num_cols = 0;
	lst = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strchr("RNOSWEAFC", line[0]) != NULL) // if the 1st char of line is one of R, N or \0, etc then do
		{
			ft_parse_R(line, map);
			ft_parse_texture(line, map);
	//		ft_parse_color(line, map);
		}
		// TODO: create 2 dimentional array for map here
		if (ft_is_map_description(line, &map_num_cols) == 1)
		{
			ft_lstadd_back(&lst, ft_lstnew(line));
			map_num_rows++;
		}
//		printf("%s\t\t\t\t => %d\n", line, ft_is_map_description(line));
		else
			free(line);
	}
	free(line);
	printf("num rows = %d, num cols = %d\n", map_num_rows, map_num_cols);
	affiche_list(lst);
	ft_convert_map_lst_to_array(lst, map, map_num_rows, map_num_cols);
	ft_lstclear(&lst, &ft_free_lst);
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
