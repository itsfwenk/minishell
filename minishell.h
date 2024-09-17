/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:51:25 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/17 17:31:21 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <dirent.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

# include "libft/libft.h"

# include "builtins/builtins.h"
# include "lexer/lexer.h"
# include "utils/ms_utils.h"

# define FALSE 0
# define TRUE 1
# define METAS "|&<>"

typedef struct s_pids
{
	int				cmd_i;
	int				status;
	int				pipefd[2];
	int				here_doc;
	pid_t			p_id;
	struct s_pids	*next;
}	t_pids;

extern int	g_signal;

int			exp_check_keys(t_string *current,
				t_skibidi *skibidishell, int *i, int *delta_char);
t_env		*key_exists(t_string *current, t_skibidi *skibidishell,
				int *limits);
void		exp_no_brackets(t_string *current,
				t_skibidi *skibidishell, int *i, int *delta_char);
int			exp_env_var(t_string *current, t_skibidi *skibidishell);
void		ft_expander(t_skibidi *skibidishell, t_token *token);
void		merge_tokens(t_skibidi *skibidishell, t_token **token,
				t_token *cmd);
void		merge_redirection(t_skibidi *skibidishell,
				t_token *current, t_token *cmd);
void		merge_arguments(t_skibidi *skibidishell,
				t_token *current, t_token *cmd);
t_token		*get_cmd(t_token *token);
void		merge_operators(t_skibidi *skibidishell, t_token *current);
int			ft_export(t_skibidi *skibidishell, char **args);
void		assemble_tstring(t_skibidi *skibidishell);
void		exp_pos_param(t_string *current, t_skibidi *skibidishell);
void		create_argv(t_token *tokens, t_skibidi *skibidishell);
t_token		*lx_meta_token(char *str, int *i, int token_type,
				t_skibidi *skibidishell);
t_token		*lx_str_token(t_skibidi *skibidishell, char *str, int *i,
				int token_type);
int			lx_createadd(t_token **tokens, t_skibidi *skibidishell,
				char *input, int *i);
t_token		*ft_lexer(char *input, t_skibidi *skibidishell);

#endif
