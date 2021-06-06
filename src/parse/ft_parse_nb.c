/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 23:05:24 by iren              #+#    #+#             */
/*   Updated: 2021/06/06 23:41:54 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_skip_to_char(char *res, char c)
{
	int	len;

	len = 0;
	if (res)
	{
		if (res[len] == '+' || res[len] == '-')
			len++;
		while (res[len] && res[len] != c && (ft_isdigit(res[len])))
		{
			len++;
		}
	}
	return (len);
}

int	ft_parse_nb(char *line, int *i, char c)
{
	int	n;

	if (ft_strchr("-+0123456789", line[*i]) && line[*i])
		n = ft_atoi(&line[*i]);
	*i += ft_skip_to_char(&line[*i], c);
	if (line[*i] == c)
		(*i)++;
	*i = ft_skip_spaces(line, *i);
	return (n);
}
