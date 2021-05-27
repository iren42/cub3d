/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 21:12:46 by iren              #+#    #+#             */
/*   Updated: 2020/09/03 10:06:56 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*s;

	if (nmemb == 0 || size == 0)
	{
		if (!(s = malloc(1)))
			return (0);
		return ((void*)s);
	}
	if (!(s = malloc(size * nmemb)))
		return (0);
	ft_bzero(s, size * nmemb);
	return ((void*)s);
}
