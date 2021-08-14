/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_tmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 00:22:45 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 14:33:16 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_content(char *line)
{
	int	i;

	i = 0;
	if (line != NULL)
	{
		if (line[0] == '\0')
			return (0);
		while (line[i] != '\0')
		{
			if (ft_strchr("10NWES ", line[i]) != NULL)
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

static int	convert_maplst_to_char(t_list *l, t_map *tmap)
{
	int	i;

	if (tmap->rows < 3 || tmap->cols < 3)
		return (FAILURE);
	tmap->map = malloc(sizeof(char *) * (tmap->rows + 1));
	if (tmap->map == NULL)
		return (FAILURE);
	i = 0;
	while (l)
	{
		tmap->map[i] = malloc(sizeof(char) * (tmap->cols + 1));
		if (tmap->map[i] == NULL || !is_map_content(l->content))
		{
			ft_free_previously_malloced(tmap->map, i);
			tmap->map = 0;
			return (FAILURE);
		}
		ft_bzero(tmap->map[i], tmap->cols + 1);
		ft_strlcpy(tmap->map[i], l->content, tmap->cols + 1);
		l = l->next;
		i++;
	}
	tmap->map[i] = 0;
	return (SUCCESS);
}

static int	check_all_parsed(t_map *tmap, int has_map_begun)
{
	if (!tmap->texture[no] || !tmap->texture[so] || !tmap->texture[we]
		|| !tmap->texture[ea] || !has_map_begun || tmap->map == 0
		|| tmap->floor == -1 || tmap->ceiling == -1)
		tmap->error = -1;
	if (!has_map_begun)
	{
		perror("Error.\nno map content.\n");
		free(tmap->map);
		tmap->map = 0;
	}
	return (tmap->error);
}

static void	loop(t_var_set_tmap *t)
{
	t->has_map_begun = is_map_content(t->line);
	while (t->has_map_begun && t->ret > 0)
	{
		ft_lstadd_back(&t->lst, ft_lstnew(t->line));
		t->tmap->rows++;
		if (ft_strlen(t->line) > (unsigned int)t->tmap->cols)
			t->tmap->cols = ft_strlen(t->line);
		t->ret = get_next_line(t->fd, &t->line);
	}
	if (ft_strchr("NSWEFC\n", t->line[0]) != NULL)
	{
		ft_parse_texture(t->line, t->tmap);
		ft_parse_color(t->line, t->tmap);
	}
	else
	{
		perror("Error.\nProhibited character was found in file descriptor.\n");
		t->tmap->error = -1;
	}
}

int	ft_set_tmap(int fd, t_map *tmap)
{
	t_var_set_tmap	t;

	t.line = 0;
	t.lst = 0;
	t.has_map_begun = 0;
	t.ret = get_next_line(fd, &t.line);
	t.fd = fd;
	t.tmap = tmap;
	while (t.ret > 0)
	{
		loop(&t);
		free(t.line);
		t.ret = get_next_line(t.fd, &t.line);
	}
	free(t.line);
	if (tmap->error == 0)
		if (convert_maplst_to_char(t.lst, tmap) == -1)
			perror("Error.\nft_set_tmap.c: An error was found in map content.\n");
	ft_lstclear(&t.lst, &free);
	return (check_all_parsed(tmap, t.has_map_begun));
}
