/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iren <iren@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 01:09:51 by iren              #+#    #+#             */
/*   Updated: 2021/02/11 21:26:35 by iren             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *last_element;

	if (alst == 0)
		return ;
	if (*alst == 0)
	{
		*alst = new;
	}
	else
	{
		last_element = ft_lstlast(*alst);
		last_element->next = new;
	}
}
