/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_lst_manip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:41:57 by fli               #+#    #+#             */
/*   Updated: 2024/09/18 18:06:17 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pids	*ft_lstnew_pipex(t_token *token, t_skibidi *skibidishell)
{
	t_pids	*n;

	n = ft_calloc(1, sizeof(t_pids));
	if (n == NULL)
		ft_free_clean(skibidishell);
	// n->token = token;
	n->p_id = -1;
	return (n);
}

void	ft_lstadd_back_pipex(t_pids **lst, t_pids *n)
{
	t_pids	*last;

	if (!lst || !n)
		return ;
	if (!(*lst))
	{
		*lst = n;
		return ;
	}
	last = *lst;
	while (last != NULL)
	{
		if ((last->next) == NULL)
		{
			last->next = n;
			return ;
		}
		last = last->next;
	}
}

void	ft_lstclear_pipex(t_pids **lst)
{
	t_pids	*temp;

	if (!lst || !*lst)
		return ;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		free(*lst);
		*lst = temp;
	}
	return ;
}
