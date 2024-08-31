/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:35:43 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/20 17:38:18 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	pwd[PATH_MAX];

	if (!(getcwd(pwd, sizeof(pwd))))
	{
		ft_print_error("pwd", NULL, "Cannot get current \
working directory path", NULL);
		return (2);
	}
	printf("%s\n", pwd);
	return (0);
}
