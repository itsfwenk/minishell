/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:29:52 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 23:11:02 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

t_skibidi	*init_shell(char **envp)
{
	t_skibidi	*shell;

	shell = ft_calloc(1, sizeof(t_skibidi));
	if (!shell || ft_export(shell, envp))
		return (NULL);
	return (shell);
}
