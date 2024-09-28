/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_pos_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:02:43 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/28 17:08:51 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	exp_dup_pos_param(char *str, char *expanded_str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$'
			&& str[i + 1] != '\0'
			&& ft_isdigit(str[i + 1]) != false)
		{
			i = i + 2;
			continue ;
		}
		expanded_str[j] = str[i];
		j++;
		i++;
	}
	expanded_str[j] = '\0';
	free(str);
	str = expanded_str;
}

void	exp_pos_param(t_skibidi *shell, char *str)
{
	int		i;
	int		nb_pos_param;
	char	*expanded_str;

	i = 0;
	nb_pos_param = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && (ft_isdigit(str[i + 1]) != false
				|| str[i + 1] == '*' || str[i + 1] == '@'))
		{
			nb_pos_param++;
			i = i + 2;
			continue ;
		}
		i++;
	}
	if (nb_pos_param == 0)
		return ;
	expanded_str = malloc(1 + (ft_strlen(str) - (2 * nb_pos_param)));
	if (expanded_str == NULL)
		exit_shell(shell);
	exp_dup_pos_param(str, expanded_str);
}
