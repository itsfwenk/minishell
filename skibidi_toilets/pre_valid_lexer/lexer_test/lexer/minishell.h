/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 14:51:25 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/12 13:44:35 by fli              ###   ########.fr       */
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

// # include "libft/libft.h"

// # include "builtins/builtins.h"
// # include "lexer/lexer.h"
// # include "utils/ms_utils.h"

# define FALSE 0
# define TRUE 1

extern int	g_signal;

#endif
