/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fnacarel <fnacarel@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 22:42:28 by fnacarel          #+#    #+#             */
/*   Updated: 2022/09/20 16:43:15 by fnacarel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*store_previous_node;

	store_previous_node = *lst;
	if (del)
	{
		while (*lst != 0 && store_previous_node != 0)
		{
			store_previous_node = *lst;
			*lst = (*lst)->next;
			del(store_previous_node -> content);
			free(store_previous_node);
		}
		lst = NULL;
	}
}
