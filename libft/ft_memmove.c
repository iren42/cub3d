/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:03:51 by iren              #+#    #+#             */
/*   Updated: 2021/06/01 14:56:37 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*s;
	char			*d;

	s = (char *)src;
	d = (char *)dest;
	if (d == s)
		return (dest);
	if (s > d)
	{
		while (n--)
			*(d++) = *(s++);
	}
	else
		while (n--)
			*(d + n) = *(s + n);
	return (dest);
}
