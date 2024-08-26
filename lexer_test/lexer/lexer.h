/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 20:55:26 by fli               #+#    #+#             */
/*   Updated: 2024/08/26 18:31:59 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <dirent.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"

typedef struct s_string
{
	char			*str;
	int				to_be_expanded;
	int				between_quote;
	struct s_string	*next;
}	t_string;

typedef struct s_token
{
	t_string		*tstring;
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
	STR,			// "
	PAR_STR,		// between parentheses
	FILENAME,		// filename
	HD_LIMITER,		// here_doc limiter string
}	t_types;

# define TRUE 1
# define FALSE 0

//////***** LEXER_UTILS *****///////

/////////// LX_LIST_ADD ///////////

int		is_word_delimiter(t_token **tokens, char *str, int i);

int		lx_createadd(t_token **tokens, char *str, int *i);

/////////// LX_LIST_MANIP_UTILS ///////////

char	*lx_strdup(char *str, int *i);

/////////// LX_LIST_MANIP ///////////

t_token	*lx_meta_token(char *str, int *i, int token_type);

t_token	*lx_str_token(t_token **tokens, char *str, int *i, int token_type);

t_token	*lx_getlast(t_token *tokens);

void	lx_addback(t_token **tokens, t_token *ntoken);

void	lx_deltokens(t_token **tokens);

/////////// LX_PARENTHESES ///////////

void	to_close_parenthesis(char *str, int *i);

char	*trim_parentheses(char *str, int *i);

/////////// LX_UTILS ///////////

int		is_sep(char *c);

int		which_token(t_token **tokens, char *c);

/////////// TSTRING_UTILS ///////////

t_string	*tstring_getlast(t_string *tstring);

void		tstring_addback(t_string **tstring, t_string *new_tstring);

void		tstring_del(t_string **tstring);

/////////// TSTRING ///////////

void	sq_tstr(char *str, int *i, t_string **tstring);

void	other_tstr(char *str, int *i, int token_type, t_string **tstring);

t_string	*create_tstring(t_token **tokens, char *str, int *i, int token_type);

/////////// TSTRING ///////////

t_token	*ft_lexer(char *input);

#endif
