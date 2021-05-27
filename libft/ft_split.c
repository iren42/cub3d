/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:32:54 by iren              #+#    #+#             */
/*   Updated: 2020/09/03 00:59:41 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_free_split(char **split, int i)
{
	if (split != 0)
	{
		while (i >= 0)
			free(split[i--]);
		free(split);
	}
	split = 0;
}

static char		*ft_fill(char *dest, const char *str, int len)
{
	int i;

	i = 0;
	if (str != 0)
	{
		if (!(dest = malloc(sizeof(char) * (len + 1))))
			return (NULL);
		while (i < len)
		{
			dest[i] = str[i];
			i++;
		}
	}
	dest[i] = '\0';
	return (dest);
}

static int		ft_nb_words(const char *s, char c)
{
	int i;
	int nb_w;

	i = 0;
	nb_w = 0;
	if (s != 0)
	{
		while (s[i])
		{
			while (s[i] == c)
				i++;
			if (s[i] != '\0' && s[i] != c)
				nb_w++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
	}
	return (nb_w);
}

static void		split_loop(const char *str, char c, int *i, int *len)
{
	if (str != 0)
	{
		while (str[*i] != c && str[*i])
		{
			(*len)++;
			(*i)++;
		}
	}
}

char			**ft_split(char const *str, char c)
{
	int		len;
	int		i;
	int		a;
	char	**res;

	a = 0;
	i = 0;
	if (!(res = malloc(sizeof(char*) * (ft_nb_words(str, c) + 1))))
		return (0);
	while (a < ft_nb_words(str, c) && !(len = 0))
	{
		split_loop(str, c, &i, &len);
		if (len > 0)
		{
			if ((res[a] = ft_fill(res[a], &str[i - len], len)) == 0)
			{
				ft_free_split(res, a);
				return (0);
			}
			a++;
		}
		i++;
	}
	res[a] = 0;
	return (res);
}
