#include "cub3d.h"
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
