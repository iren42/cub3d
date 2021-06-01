/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 19:32:54 by iren              #+#    #+#             */
/*   Updated: 2021/05/31 19:44:37 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_split(char **split, int i)
{
	if (split != 0)
	{
		while (i >= 0)
			free(split[i--]);
		free(split);
	}
	split = 0;
}

static int	ft_nb_words(const char *s, char c)
{
	int	i;
	int	nb_w;

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

static char	*ft_copy(char *dest, char const *src, int i, int *word_len)
{
	int	j;

	j = 0;
	dest = malloc(sizeof(char) * (*word_len + 1));
	if (dest == NULL)
		return (NULL);
	dest[*word_len] = '\0';
	while (*word_len > 0)
	{
		dest[j++] = src[i - *word_len];
		(*word_len)--;
	}
	return (dest);
}

static int	ft_calc_word_len(char const *str, int *i, char c)
{
	int	len;

	len = 0;
	while (str[*i] != '\0' && str[*i] == c)
		(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
	{
		len++;
		(*i)++;
	}
	return (len);
}

char	**ft_split(char const *str, char c)
{
	int		word_len;
	int		i;
	int		row;
	char	**res;
	int		nb_w;

	row = -1;
	nb_w = ft_nb_words(str, c);
	i = 0;
	word_len = 0;
	res = malloc(sizeof(char *) * (nb_w + 1));
	if (res == NULL)
		return (0);
	while (++row < nb_w)
	{	
		word_len = ft_calc_word_len(str, &i, c);
		res[row] = ft_copy(res[row], str, i, &word_len);
		if (res[row] == NULL)
		{
			ft_free_split(res, row);
			return (0);
		}
	}
	res[row] = 0;
	return (res);
}
