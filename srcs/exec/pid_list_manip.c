/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_list_manip.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:28:06 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 17:29:50 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

t_pid	*ft_lstnew_pipex(t_skibidi *shell)
{
	t_pid	*n;

	n = ft_calloc(1, sizeof(t_pid));
	if (n == NULL)
		exit_shell(shell);
	n->p_id = -1;
	n->pipefd[0] = -1;
	n->pipefd[1] = -1;
	return (n);
}
