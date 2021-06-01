/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 16:59:03 by iren              #+#    #+#             */
/*   Updated: 2021/05/31 20:34:06 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_calc_len(char const *s1, char const *s2)
{
	unsigned int	len;

	len = 0;
	while (*s1++)
		len++;
	while (*s2++)
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	unsigned int	len;
	unsigned int	i;
	unsigned int	j;

	res = 0;
	if (s1 == 0 || s2 == 0)
		return (0);
	len = ft_calc_len(s1, s2);
	res = malloc(sizeof(char) * (len + 1));
	if (res == NULL)
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
