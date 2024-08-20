/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:50:41 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/20 19:21:39 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;

// 	(void)argv;
// 	(void)argc;
// 	env = NULL;
// 	ft_export(&env, envp);
// 	ft_export(&env, &argv[1]);
// 	free_env(env);
// 	return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	(void)argc;
	env = NULL;
	ft_export(&env, envp);
	// ft_export(&env, &argv[1]);
	ft_exit(&argv[1]);
	free_env(env);
	return (0);
}
