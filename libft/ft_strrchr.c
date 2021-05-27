/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:44:33 by iren              #+#    #+#             */
/*   Updated: 2020/09/03 10:26:30 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *st, int c)
{
	int		i;
	char	*res;

	i = 0;
	res = 0;
	while (st[i])
	{
		if (c == st[i])
			res = (char*)&st[i];
		i++;
	}
	if (c == '\0')
		return ((char*)&st[i]);
	return ((char*)res);
}
