/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_tmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 00:22:45 by iren              #+#    #+#             */
/*   Updated: 2021/06/06 15:55:38 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_linemap_desc(char *line, int *map_num_cols)
{
	int	i;

	i = 0;
	if (line[0] == '\0')
		return (0);
	while (line[i] != '\0')
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

static void	lstadd_line_or_free(t_list **lst, char *line, int *rows, int *cols)
{
	if (is_linemap_desc(line, cols) == 1)
	{
		ft_lstadd_back(lst, ft_lstnew(line));
		*rows = *rows + 1;
	}
	else
	{
		free(line);
	}
}

static int	convert_maplst_to_char(t_list *l, t_map *map, int rows, int cols)
{
	int	i;

	map->map = malloc(sizeof(char *) * (rows + 1));
	if (map->map == NULL)
		return (FAILURE);
	i = 0;
	while (l)
	{
		map->map[i] = ft_strdup(l->content);
		if (map->map[i] == NULL)
		{
			ft_free_previously_malloced(map->map, i);
			return (FAILURE);
		}
		l = l->next;
		i++;
	}
	map->map[i] = 0;
	map->rows = rows;
	map->cols = cols;
	return (SUCCESS);
}

static void	ft_init(int *rows, int *cols, t_list **lst)
{
	*rows = 0;
	*cols = 0;
	*lst = 0;
}

int	ft_set_tmap(int fd, t_map *map)
{
	int		ret;
	char	*line;
	int		rows;
	int		cols;
	t_list	*lst;

	line = 0;
	ft_init(&rows, &cols, &lst);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		if (ft_strchr("RNOSWEAFC", line[0]) != NULL)
		{
			ft_parse_R(line, map);
			ft_parse_texture(line, map);
			ft_parse_color(line, map);
		}
		lstadd_line_or_free(&lst, line, &rows, &cols);
		ret = get_next_line(fd, &line);
	}
	lstadd_line_or_free(&lst, line, &rows, &cols);
	convert_maplst_to_char(lst, map, rows, cols);
	ft_lstclear(&lst, &free);
	return (SUCCESS);
}
