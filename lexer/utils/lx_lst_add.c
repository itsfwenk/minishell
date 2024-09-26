/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lx_lst_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:28:57 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/26 13:25:27 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	set_end_index(char *str, int start, int end, int *i)
// {
// 	if (str[start] == '\"' || str[start] == '\'')
// 	{
// 		while (str[end] != str[start])
// 		{
// 			end++;
// 		}
// 		dprintf(2, "start = %d\n", start);
// 		dprintf(2, "end = %d = %c\n", end, str[end]);
// 		i[1] = end + 1;
// 		dprintf(2, "i[1]= %d\n", i[1]);
// 		set_end_index(str, end + 1, end + 2, i);
// 		// dprintf(2, "start = %d\n", start);
// 		// dprintf(2, "end = %d = %c\n", end, str[end]);
// 	}
// }

int	is_word_delimiter(t_token **tokens, char *str, int *i)
{
	int	char_type;

	// dprintf(2, "i[0] = %d\n", i[0]);
	// dprintf(2, "i[1] = %d\n", i[1]);
	if (str[i[1]] == ' ' || str[i[1]] == '\t' || str[i[1]] == '\0')
		return (TRUE);
	char_type = which_token(tokens, &str[i[1]]);
	if (char_type >= PIPE && char_type <= HERE_DOC)
		return (TRUE);
	else
		return (FALSE);
}

int	lx_createadd(t_token **tokens, t_skibidi *skibidishell, char *input, int *i)
{
	t_token	*ntoken;
	int		token_type;
	// dprintf(2, "creating tokens \n");
	token_type = which_token(tokens, &input[i[0]]);
	if (token_type >= PIPE && token_type <= HERE_DOC)
		ntoken = lx_meta_token(input, i, token_type, skibidishell);
	else
		ntoken = lx_str_token(skibidishell, input, i, token_type);
	if (ntoken == NULL)
		ft_free_clean(skibidishell);
	lx_addback(tokens, ntoken);
	return (TRUE);
}
