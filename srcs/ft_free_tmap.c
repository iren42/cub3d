#include "cub3d.h"

void	ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	free(map->texture[No]);
	free(map->texture[So]);
	free(map->texture[We]);
	free(map->texture[Ea]);
	free(map->texture);
	while (map->map[i] != 0)
		free(map->map[i++]);
	free(map->map);
//	free(map->sprite); // TODO: parsing for sprite, floor, ceiling
//	free(map->floor);
//	free(map->ceiling);
}
