#include "cub3d.h"

void	ft_free_previously_malloced(char **tab, int i)
{
	if (tab != 0)
	{
		while (i >= 0)
			free(tab[i--]);
		free(tab);
	}
	tab = 0;
}
