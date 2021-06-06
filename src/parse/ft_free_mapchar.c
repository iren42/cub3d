#include "cub3d.h"

void	ft_free_mapchar(char **map)
{
	int	i;

	i = 0;
	while (map[i] != 0)
	{
		free(map[i++]);
	}
	free(map);
}
