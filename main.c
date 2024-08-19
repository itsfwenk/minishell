/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:16:56 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 12:41:08 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "builtins/builtins.h"
#include <stdio.h>

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1)
		printf("%d\n", check_key(argv[1]));
	return (0);
}
