/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_tmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 00:22:45 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 07:12:21 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_content(char *line, t_map *tmap)
{
	int	i;

	i = 0;
	if (line[0] == '\0')
		return (0);
	while (line[i] != '\0')
	{
		if (ft_strchr("10NWES", line[i]) != NULL || ft_isspace(line[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	ft_has_proh_char(char *line)
{
	int	i;

	i = 0;
	if (line != NULL)
	{
		while (line[i])
		{
			if (ft_isspace(line[i]) || ft_strchr("10NSWE", line[i]) != NULL)
				i++;
			else
			{
				perror("Error.\nInvalid character in file descriptor.\n");
				return (1);
			}
		}
	}
	return (0);
}

static int	convert_maplst_to_char(t_list *l, t_map *tmap)
{
	int	i;

	tmap->map = malloc(sizeof(char *) * (tmap->rows + 1));
	if (tmap->map == NULL)
		return (FAILURE);
	i = 0;
	while (l)
	{
		tmap->map[i] = malloc(sizeof(char) * (tmap->cols + 1));
		if (tmap->map[i] == NULL || ft_has_proh_char(l->content))
		{
	//		printf("i %d proh char in %s\n", i, (char*)l->content);
			ft_free_previously_malloced(tmap->map, i);
			tmap->map = 0;
			tmap->error = -1;
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

int	ft_check_all_parsed(t_map *tmap)
{
	if (!tmap->texture[No] || !tmap->texture[So] || !tmap->texture[We]
		|| !tmap->texture[Ea] || tmap->floor == -1 || tmap->ceiling == -1)
		tmap->error = -1;
		printf("tmap error %d ceiling %d\n", tmap->error, tmap->ceiling);
	return (tmap->error);
}

int	ft_set_tmap(int fd, t_map *tmap)
{
	int		ret;
	char	*line;
	int		has_map_begun;
	t_list	*lst;

	line = 0;
	lst = 0;
	has_map_begun = 0;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		has_map_begun = is_map_content(line, tmap);
		while (has_map_begun && ret > 0)
		{
			ft_lstadd_back(&lst, ft_lstnew(line));
			tmap->rows++;
			if (ft_strlen(line) > tmap->cols)
				tmap->cols = ft_strlen(line);
			ret = get_next_line(fd, &line);
		}
		if (ft_strchr("NSWEFC\n", line[0]) != NULL)
		{
			ft_parse_texture(line, tmap);
			ft_parse_color(line, tmap);
			free(line);
		}
		else // Proh char
		{
			perror("Error.\nFile descriptor has prohibited character.\n");
			tmap->error = -1;
			free(line);
		}
		ret = get_next_line(fd, &line);
	}
//	printf("line : %s rows %d cols %d\n", line, tmap->rows, tmap->cols);
	free(line);
//	affiche_list(lst);
	if (tmap->error == 0)
		if (convert_maplst_to_char(lst, tmap) == -1)
			perror("Error.\nAn error was found in map content.\n");
	ft_lstclear(&lst, &free);
//	printf("tmap error %d\n", tmap->error);
	return (ft_check_all_parsed(tmap));
}
