/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:45:00 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/20 17:18:53 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_color(char *msg, char *color)
{
	printf("%s%s%s", color, msg, END_COLOR);
}

void	ft_print_error(char *cmd, char *arg, char *error, char *seps)
{
	if (!arg)
		ft_dprintf(2, "%sskibidishell: %s: %s%s", RED, cmd, error, \
		END_COLOR);
	else
		ft_dprintf(2, "%sskibidishell: %s: %c%s%c: %s%s", RED, cmd, \
		seps[0], arg, seps[1], error, END_COLOR);
	ft_dprintf(2, "\n");
}

char	*ft_get_prompt(int err)
{
	if (err)
		return (ERROR_EMOJI BOLD RED PROMPT END_COLOR);
	return (SUCCESS_EMOJI BOLD GREEN PROMPT END_COLOR);
}
