/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_nb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 23:05:24 by iren              #+#    #+#             */
/*   Updated: 2021/08/13 09:17:39 by iren             ###   ########.fr       */
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

int	ft_parse_nb(char *line, unsigned int *i, char c)
{
	int	n;

	if (line[*i] == '\0')
		return (-1);
	n = -1;
	if (ft_strchr("-+0123456789", line[*i]) && line[*i])
		n = ft_atoi(&line[*i]);
	*i += ft_skip_to_char(&line[*i], c);
	if (line[*i] == c)
		(*i)++;
	*i = ft_skip_spaces(line, *i);
	return (n);
}
