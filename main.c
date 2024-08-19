/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:16:56 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 16:54:58 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "builtins/builtins.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	size_t	i;

	env = NULL;
	i = 0;
	ft_export(&env, envp);
	add_env(&env, "SHELL", "minishell");
	ft_env(env);
	free_env(env);
	return (0);
}
