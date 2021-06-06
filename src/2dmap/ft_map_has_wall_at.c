#include "cub3d.h"

int	ft_map_has_wall_at(float x, float y)
{
	int map_grid_index_x;
	int map_grid_index_y;

	if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT) // out of boundary
		return (1);
	map_grid_index_x = floor(x / TILE_SIZE);
	map_grid_index_y = floor(y / TILE_SIZE);
//	printf("index x = %d\t y = %d\t %d\n", map_grid_index_x, map_grid_index_y, 
//		map[map_grid_index_y][map_grid_index_x]);
	return (map[map_grid_index_y][map_grid_index_x] != 0);
}
