#include "cub3d.h"

void	ft_free_tmap(t_map *map)
{
	int	i;

	i = 0;
	free(map->texture);
	while (map->map[i] != 0)
		free(map->map[i++]);
	free(map->map);
}
