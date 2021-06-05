#include "cub3d.h"

char	**ft_mirror(char **map, int rows, int cols)
{
	int		i;
	int		j;
	char	buffer;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols / 2)
		{
			buffer = map[i][j];
			map[i][j] = map[i][cols - 1 - j];
			map[i][cols - 1 - j] = buffer;
			j++;
		}
		i++;
	}
	return (map);
}
