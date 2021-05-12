#include "cub3d.h"

void	ft_free_map(t_map *map)
{
	free(map->no);
	free(map->so);
	free(map->we);
	free(map->ea);
//	free(map->sprite); // TODO: parsing for sprite, floor, ceiling
//	free(map->floor);
//	free(map->ceiling);
}
