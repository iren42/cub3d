/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:05:51 by iren              #+#    #+#             */
/*   Updated: 2021/04/17 20:37:20 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strnstr(const char *cbig, const char *clittle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len++;
	if (ft_strncmp(clittle, "", 1) == 0)
		return ((char*)cbig);
	while (cbig[i] && --len)
	{
		len += j;
		j = 0;
		if (cbig[i] == clittle[j])
		{
			while (cbig[i + j] == clittle[j] && len--)
			{
				j++;
				if (clittle[j] == '\0')
					return ((char*)&cbig[i]);
			}
		}
		i++;
	}
	return (0);
}
