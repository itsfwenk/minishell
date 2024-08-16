/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:16:56 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/16 19:16:46 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "builtins/builtins.h"

int	main(int argc, char **argv, char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		ft_dprintf(1, "%s\n", envp[i]);
		i++;
	}
	return (0);
}
