/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 19:45:02 by iren              #+#    #+#             */
/*   Updated: 2020/10/29 22:19:47 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	res;

	res = 0;
	while (str[res])
		res++;
	return (res);
}

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	char	*res;
	size_t	strlen;

	if (str != 0)
	{
		strlen = 0;
		while (str[strlen])
			strlen++;
		if (start > (unsigned int)strlen)
			start = (unsigned int)strlen;
		if (start + len > strlen)
			len = strlen - start;
		res = malloc(sizeof(char) * (len + 1));
		if (res == NULL)
			return (0);
		ft_memmove(res, &str[start], len);
		res[len] = '\0';
		return (res);
	}
	return (0);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*s;
	char			*d;
	unsigned int	i;

	i = -1;
	s = (char *)src;
	d = (char *)dest;
	if (d == s)
		return ((void *)d);
	if (s > d)
		while (++i < n)
			*(d + i) = *(s + i);
	else
		while (n--)
			d[n] = s[n];
	return ((void *)d);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*res;
	char			*start_s2;
	unsigned int	len;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (0);
	len = 0;
	start_s2 = (char *)s2;
	while (s1[len])
		len++;
	while (*start_s2++)
		len++;
	res = malloc(sizeof(char) * (len + 1));
	if (res == 0)
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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*st;

	i = 0;
	st = (char *)s;
	while (st[i])
	{
		if (c == st[i])
			return (&st[i]);
		i++;
	}
	if (c == '\0')
		return (&st[i]);
	return ((char *)0);
}
