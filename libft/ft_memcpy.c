/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 18:14:53 by iren              #+#    #+#             */
/*   Updated: 2020/09/03 10:14:59 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	i = 0;
	s = (unsigned char*)src;
	d = (unsigned char*)dest;
	if (src == 0 && dest == 0)
		return (dest);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((void*)d);
}
