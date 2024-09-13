/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:51:25 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/13 17:26:53 by mel-habi         ###   ########.fr       */
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

# include "libft/libft.h"

# include "builtins/builtins.h"
# include "lexer/lexer.h"
# include "utils/ms_utils.h"

# define FALSE 0
# define TRUE 1
# define METAS "|&<>"

extern int	g_signal;

int			exp_check_keys(t_string *current,
				t_skibidi *skibidishell, int *i, int *delta_char);
t_env		*key_exists(t_string *current, t_skibidi *skibidishell, int *limits);
void		exp_no_brackets(t_string *current,
				t_skibidi *skibidishell, int *i, int *delta_char);
int			exp_env_var(t_string *current, t_skibidi *skibidishell);
void		ft_expander(t_skibidi *skibidishell, t_token *token);
void		merge_tokens(t_skibidi *skibidishell, t_token **token, t_token *cmd);

#endif
