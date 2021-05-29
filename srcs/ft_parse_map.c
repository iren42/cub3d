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

int	ft_is_filename_valid(char *name)
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

void	ft_display_tmap_map(t_map map)
{
	int	i;

	i = 0;
	while (map.map[i] != 0)
	{
		printf("%s\n", map.map[i]);
		i++;
	}
}

void	ft_display_chararray(char **map)
{
	int	i;

	i = 0;
	while (map[i] != 0)
	{
		printf("%s\n", map[i]);
		i++;
	}
}

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
		map->map[i] = ft_strdup(l->content); // TODO: free it
		if (map->map[i] == NULL)
			return (FAILURE);
		l = l->next;
		i++;
	}
	map->map[i] = 0;
	map->nb_map_rows = rows;
	map->nb_map_cols = cols;
//	ft_display_tmap_map(*map);
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

int	ft_set_tmap(int fd, t_map *map)
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
		if (ft_is_map_description(line, &map_num_cols) == 1)
		{
			ft_lstadd_back(&lst, ft_lstnew(line));
			map_num_rows++;
		}
		else
			free(line);
	}
	if (ft_is_map_description(line, &map_num_cols) == 1)
	{
		ft_lstadd_back(&lst, ft_lstnew(line));
		map_num_rows++;
	}
	else
		free(line);
	printf("num rows = %d, num cols = %d\n", map_num_rows, map_num_cols);
	affiche_list(lst);
	ft_convert_map_lst_to_array(lst, map, map_num_rows, map_num_cols);
	ft_lstclear(&lst, &free); // free or ft_free_lst ?
	return (SUCCESS);
}

int	ft_does_map_have_only_one_player(char **tab, int *player_x, int *player_y)
{
	int nb_players;
	int	i;
	int	j;

	nb_players = 0;
	i = 0;
	while (tab[i] != 0)
	{
		j = 0;
		while (tab[i][j] != '\0')
		{
			if (tab[i][j] == 'N' || tab[i][j] == 'E' || tab[i][j] == 'W' || tab[i][j] == 'S')
			{
				nb_players++;
				*player_x = i;
				*player_y = j;
			}
			j++;
		}
		i++;
	}
	//	printf("number of player (must be 1) : %d (%d, %d)\n", nb_players, *player_x, *player_y);
	if (nb_players != 1)
		return (0);
	return (1);
}

void	ft_spread_b(char **map, int x, int y, int nb_rows, int nb_cols)
{

	if (x >= 0 && x <= nb_rows - 1 && y >= 0 && y <= nb_cols - 1)
	if (map[x][y] == '0' || map[x][y] == '2' )
	{
		map[x][y] = 'b';
		ft_spread_b(map, x + 1, y, nb_rows, nb_cols);
		ft_spread_b(map, x - 1, y, nb_rows, nb_cols);
		ft_spread_b(map, x, y + 1, nb_rows, nb_cols);
		ft_spread_b(map, x, y - 1, nb_rows, nb_cols);
	}
}

char	**ft_copy_maparray(char **map, int nb_rows, int nb_cols)
{
	char	**res;
	int		i;

	i = 0;
	printf("HERE\n");
	res = malloc(sizeof(char*) * (nb_rows + 1));
	if (res != NULL)
	{
		while (map[i] != 0)
		{
		//	res[i] = ft_strdup(map[i]);
			res[i] = malloc(sizeof(char) * (nb_cols + 1));
			ft_bzero(res[i], nb_cols + 1);
			ft_memmove(res[i], map[i], ft_strlen(map[i]));
			i++;
		}
		res[i] = 0;
	}
	printf("HERE\n");
	return (res);
}

int		ft_is_b_found_in_prohibited_areas_vert(char **map, int nb_rows)
{
	int i;
	int j;

	i = 0;
	while (map[0][i] != '\0')
		if (map[0][i++] == 'b')
			return (1);
	while (j < nb_rows - 1)
	{
		i = 0;
		if (map[j][0] == 'b') // regarde le bord gauche de la ligne j
			return (1);
		while (map[j][i] != '\0' && map[j][i] != ' ') // aller a la fin de la ligne j
			i++;
		if (map[j][i - 1] == 'b') // regarde le bord droit
			return (1);
		j++;
	}
	i = 0;
	while (map[nb_rows - 1][i] != '\0')
		if (map[nb_rows - 1][i++] == 'b')
			return (1);
	return (0);
}

char	**ft_turn_chararray(char **map, int rows, int cols)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	res = malloc(sizeof(char*) * (cols + 1));
	if (res != NULL)
	{
		j = 0;
		while (i < cols)
		{
			j = 0;
			res[i] = malloc(sizeof(char) * (rows + 1));
			while (j < rows)
			{
				if (map[j][i] == '\0')
					res[i][j] = ' ';
				else
					res[i][j] = map[j][i];
				j++;
			}
			res[i][j] = '\0';
			i++;
		}
		res[i] = 0;
	}
	ft_display_chararray(res);
	return (res);
}

int	ft_is_map_closed(t_map map, int px, int py)
{
	char	**tab;
	char	**tab_turned;

	tab = ft_copy_maparray(map.map, map.nb_map_rows, map.nb_map_cols); // TODO:free it
	ft_display_chararray(tab);
	tab[px][py] = '0';
	ft_spread_b(tab, px, py, map.nb_map_rows, map.nb_map_cols);
	printf("After propagation:\n");
	ft_display_chararray(tab);
	printf("Turn array\n\n\n");
	tab_turned = ft_turn_chararray(tab, map.nb_map_rows, map.nb_map_cols);
	if (ft_is_b_found_in_prohibited_areas_vert(tab, map.nb_map_rows)
	|| ft_is_b_found_in_prohibited_areas_vert(tab_turned, map.nb_map_cols) // TODO: mirrors
	)
	{
		printf("b was found. Oops\n");
		return (0);
	}
	return (1);
}

int	ft_is_map_valid(t_map *map)
{
	int player_x;
	int	player_y;

	if (ft_does_map_have_only_one_player(map->map, &player_x, &player_y) != 1)
		return (0);
//	ft_display_tmap_map(*map);
	if (!ft_is_map_closed(*map, player_x, player_y))
		return (0);
	return (1);
}

int ft_parse_map(char *name, t_map *map)
{
	int fd;

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
