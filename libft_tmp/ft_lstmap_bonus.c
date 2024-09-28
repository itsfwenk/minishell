/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:24:36 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/23 14:35:59 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*el;

	if (!(lst && f))
		return (NULL);
	first = ft_lstnew(f(lst->content));
	if (!first)
		return (NULL);
	el = first;
	lst = lst->next;
	while (lst)
	{
		el->next = ft_lstnew(f(lst->content));
		if (!el->next)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		el = el->next;
		lst = lst->next;
	}
	el->next = NULL;
	return (first);
}
