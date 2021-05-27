/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:59:03 by iren              #+#    #+#             */
/*   Updated: 2021/02/11 21:34:18 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	char			*start_s2;
	unsigned int	len;
	unsigned int	i;
	unsigned int	j;

	res = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	len = 0;
	start_s2 = (char*)s2;
	while (s1[len])
		len++;
	while (*start_s2++)
		len++;
	if (!(res = malloc(sizeof(char) * (len + 1))))
		return (0);
	i = -1;
	j = -1;
	while (s1[++i])
		res[i] = s1[i];
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	return (res);
}
