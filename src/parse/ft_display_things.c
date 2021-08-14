/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_things.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 19:36:58 by iren              #+#    #+#             */
/*   Updated: 2021/08/14 14:33:47 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	affiche_str(void *c)
{
	static int	i = 0;

	printf("L %d:\t\t%s\n", i++, (char *) c);
}

void	affiche_list(t_list *l)
{
	printf("\nLIST BEGIN-----\n");
	if (l != 0)
		ft_lstiter(l, &affiche_str);
	printf("END-----\n");
}

void	ft_display_tmap(t_map map)
{
	if (map.map != 0)
	{
		printf("no = %s\n", map.texture[no]);
		printf("so = %s\n", map.texture[so]);
		printf("ea = %s\n", map.texture[ea]);
		printf("we = %s\n", map.texture[we]);
		printf("error = %d\n", map.error);
	}
}

void	ft_display_tmap_map(t_map map)
{
	int	i;

	i = 0;
	if (map.map != 0)
	{
		while (map.map[i] != 0)
		{
			printf("%s\n", map.map[i]);
			i++;
		}
	}
}

void	ft_display_chararray(char **map)
{
	int	i;

	i = 0;
	if (map != 0)
	{
		while (map[i] != 0)
		{
			printf("%s\n", map[i]);
			i++;
		}
	}
}
