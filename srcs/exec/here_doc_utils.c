/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:17:15 by fli               #+#    #+#             */
/*   Updated: 2024/10/07 16:47:10 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

static void	cp_limiter(char	*limiter, t_token *limiter_token)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (limiter_token->full_string[i] != '\0')
	{
		if (in_charset(limiter_token->full_string[i], "'\"") == false)
		{
			limiter[j] = limiter_token->full_string[i];
			j++;
		}
		i++;
	}
	limiter[j] = '\0';
}

char	*get_limiter(t_skibidi *shell, t_token *limiter_token)
{
	int		i;
	int		len;
	char	*limiter;

	i = 0;
	len = 0;
	while (limiter_token->full_string[i] != '\0')
	{
		i++;
		if (in_charset(limiter_token->full_string[i], "'\"") == false)
			len++;
	}
	limiter = ft_calloc(len + 1, sizeof(char));
	if (limiter == NULL)
		exit_shell(shell);
	cp_limiter(limiter, limiter_token);
	return (limiter);
}
