/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:44:11 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/28 15:46:22 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_clean(t_skibidi *skibidishell)
{
	free_env(skibidishell->env);
	lx_deltokens(&skibidishell->tokens);
	free(skibidishell);
}
