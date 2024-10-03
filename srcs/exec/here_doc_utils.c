/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:17:15 by fli               #+#    #+#             */
/*   Updated: 2024/10/03 19:17:41 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

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
	i = 0;
	while (limiter_token->full_string[i] != '\0')
	{
		if (in_charset(limiter_token->full_string[i], "'\"") == false)
			limiter[i] = limiter_token->full_string[i];
		i++;
	}
	limiter[i] = '\0';
	return (limiter);
}
