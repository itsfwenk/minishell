/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:10:27 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/31 14:43:46 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

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
	char			*full_string; //
	int				type;
	struct s_token	*sub_shell;
	struct s_token	*next;
}	t_token;

typedef enum e_types
{
	PIPE,
	IN_REDIR,
	OUT_REDIR,
	OR,
	AND,
	APD_OUT_REDIR,
	HERE_DOC,
	STR,
	PAR_STR,
	FILENAME,
	HD_LIMITER,
}	t_types;

typedef struct s_leaf
{
	int				in;
	int				out;
	char			*infile;
	char			*outfile;
	t_string		*cmd;
	t_string		*args;
	struct s_leaf	*next;
}	t_leaf;

// utils
int			is_word_delimiter(t_token **tokens, char *str, int i);
int			lx_createadd(t_token **tokens, char *str, int *i);
char		*lx_strdup(char *str, int *i);
char		*lx_strictstrdup(char *str, int *i); //
t_token		*lx_meta_token(char *str, int *i, int token_type);
t_token		*lx_str_token(t_token **tokens, char *str, int *i, int token_type);
t_token		*lx_getlast(t_token *tokens);
void		lx_addback(t_token **tokens, t_token *ntoken);
void		lx_deltokens(t_token **tokens);
void		to_close_parenthesis(char *str, int *i);
char		*trim_parentheses(char *str, int *i);
int			is_sep(char *c);
int			which_token(t_token **tokens, char *c);
t_string	*tstring_getlast(t_string *tstring);
void		tstring_addback(t_string **tstring, t_string *new_tstring);
void		tstring_del(t_string **tstring);
void		sq_tstr(char *str, int *i, t_string **tstring);
void		other_tstr(char *str, int *i, int token_type, t_string **tstring);
t_string	*create_tstring(char *str, int *i, int token_type);

t_token		*ft_lexer(char *input);

#endif
