/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:29:52 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 11:42:09 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

t_skibidi	*init_shell(void)
{
	t_skibidi	*shell;

	shell = ft_calloc(1, sizeof(t_skibidi));
	if (!shell)
		return (NULL);
	return (shell);
}
