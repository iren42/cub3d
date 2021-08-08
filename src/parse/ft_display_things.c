#include "cub3d.h"
void	affiche_str(void *c)
{
	printf("line: %s\n", (char*)c);
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
//	printf("res_x = %d\n", map.res_x);
//	printf("res_y = %d\n", map.res_y);
	printf("no = %s\n", map.texture[No]);
	printf("so = %s\n", map.texture[So]);
	printf("ea = %s\n", map.texture[Ea]);
	printf("we = %s\n", map.texture[We]);
	printf("error = %d\n", map.error);
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
