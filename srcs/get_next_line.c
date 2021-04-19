/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 17:00:20 by iren              #+#    #+#             */
/*   Updated: 2021/04/17 22:09:40 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char **str, int *len)
{
	char	buffer[32 + 1];
	char	*tmp;

	tmp = 0;
	while ((*len = read(fd, buffer, 32)) > 0)
	{
		buffer[*len] = '\0';
		tmp = *str;
		*str = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr((char*)*str, '\n') != 0)
			break ;
	}
	return (*str);
}

static void	manage_strs(char **str, char **saved_str)
{
	char	*tmp;

	tmp = *str;
	*saved_str = ft_substr(*str, ft_strchr(*str, '\n') - *str + 1,
				ft_strlen(*str));
	*str = ft_substr(tmp, 0, ft_strchr(tmp, '\n') - tmp);
	free(tmp);
}

int			get_next_line(int fd, char **line)
{
	static char	*str;
	static char	*saved_str;
	int			len;

	*line = 0;
	if (fd < 0 || line == 0)
		return (-1);
	if (!saved_str)
		str = ft_substr("", 0, 1);
	if (saved_str)
	{
		str = saved_str;
		saved_str = 0;
	}
	str = read_line(fd, &str, &len);
	if (ft_strchr(str, '\n') != 0)
		manage_strs(&str, &saved_str);
	*line = str;
	if (len < 0)
		return (-1);
	if (len == 0 && saved_str == 0)
		return (0);
	return (1);
}
