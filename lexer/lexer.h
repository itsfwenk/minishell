/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:55:26 by fli               #+#    #+#             */
/*   Updated: 2024/08/20 14:24:17 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <dirent.h>
# include <linux/limits.h>
# include "../libft/libft.h"

typedef struct s_token
{
	char			*str;
	char			*type;
	struct s_token	*next;
}	t_token;

# define TRUE 1
# define FALSE 0

/////////// LIST_MANIP ///////////

t_token	*lx_newtoken(char *str, int i, int j);

t_token	*lx_getlast(t_token *tokens);

void	lx_addback(t_token **tokens, t_token *ntoken);

void	lx_createadd(t_token **tokens, char *str, int i, int j);

void	lx_deltokens(t_token **tokens);

/////////// LIST_MANIP_UTILS ///////////

char	*lx_strdup(char *str, int i, int j);

#endif
