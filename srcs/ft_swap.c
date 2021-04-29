#include "cub3d.h"

void	ft_swap(float *a, float *b)
{
	float buffer;

	buffer = *a;
	*a = *b;
	*b = buffer;
}
