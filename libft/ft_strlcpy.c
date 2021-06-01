/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 02:18:40 by iren              #+#    #+#             */
/*   Updated: 2021/06/01 23:53:04 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *s, size_t size)
{
	size_t	len;

	len = 0;
	if (s != 0)
	{
		while (s[len])
			len++;
		if (size == 0)
			return (len);
		while (*(s++) && --size)
			*dest++ = *(s - 1);
		*dest = '\0';
	}
	return (len);
}
