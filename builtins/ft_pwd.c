/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:35:43 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/16 19:52:19 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_dprintf(2, "minishell: pwd: Cannot get current working directory path\n");
		return (2);
	}
	ft_dprintf(1, "%s\n", pwd);
	free(pwd);
	return (0);
}
