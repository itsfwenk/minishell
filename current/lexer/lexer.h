/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:55:26 by fli               #+#    #+#             */
/*   Updated: 2024/08/22 18:07:22 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

// # include <stdio.h>
// # include <errno.h>
// # include <stdlib.h>
// # include <dirent.h>
// # include <linux/limits.h>
// # include "../libft/libft.h"

typedef struct s_token
{
	char			*value;
	int				to_be_expanded;
	int				type;
	struct s_token	*sub_shell;
	struct s_token	*next;
}	t_token;

typedef enum	e_types
{
	// 1 char
	PIPE,			// |
	IN_REDIR,		// <
	OUT_REDIR,		// >
	// 2 char
	OR,				// ||
	AND,			// &&
	APD_OUT_REDIR,	// >>
	HERE_DOC,		// <<
	// str
	DQ_STR,			// "
	SQ_STR,			// '
	PAR_STR,		// between parentheses
	EXEC,			// executable
	ARG,			// arguments
	FILENAME,		// filename
	HD_LIMITER,		// here_doc limiter string
}	t_types;

# define TRUE 1
# define FALSE 0

/////////// LIST_ADD ///////////

void	lx_createadd(t_token **tokens, char *str, int *i);

/////////// LIST_MANIP_UTILS ///////////

char	*lx_strdup(char *str, int *i);

/////////// LIST_MANIP ///////////

t_token	*lx_newtoken(t_token **tokens, char *str, int *i, int token_type);

t_token	*lx_getlast(t_token *tokens);

void	lx_addback(t_token **tokens, t_token *ntoken);

void	lx_deltokens(t_token **tokens);

/////////// LX_UTILS ///////////

int		is_sep(char *c);

int		which_token(t_token **tokens, char *c);

#endif
