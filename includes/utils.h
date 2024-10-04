/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:32:23 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/04 16:24:10 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define RED "\e[31m"
# define GREEN "\e[32m"
# define YELLOW "\e[33m"
# define BLUE "\e[34m"
# define PURPLE "\e[35m"
# define CYAN "\e[36m"
# define WHITE "\e[0m"
# define END_COLOR "\e[0m"
# define BOLD "\e[1m"

# define PROMPT " skibidishell > "
# define SUCCESS_EMOJI "😸"
# define WARNING_EMOJI "🙀"
# define ERROR_EMOJI "😿"

// Enums
typedef enum e_side			t_side;
typedef enum e_type			t_type;

// Structures
typedef struct s_pid		t_pid;
typedef struct s_env		t_env;
typedef struct s_string		t_string;
typedef struct s_token		t_token;
typedef struct s_kibidi		t_skibidi;

// char_utils.c
bool		in_charset(char c, char *charset);
bool		is_space(char c);
bool		is_meta(char c);
char		is_quote(char c);

// free_utils.c
char		**free_str_tab(char	**tab);
int			exit_shell(t_skibidi *shell);
void		free_env(t_env	*env);

// init_utils.c
t_skibidi	*init_shell(char **envp);

// line_utils.c
bool		check_line(char *line);

// only_redirs_utils.c
bool		only_redirs(t_token *token);
void		check_for_here_doc(t_skibidi *shell, t_token *token);
bool		expd_wc_only_redir(t_skibidi *shell, t_token *current);
void		open_only_redir(t_skibidi *shell, t_token *token);

// print_utils.c
void		ft_print_color(char *msg, char *color);
void		ft_print_error(char *cmd, char *arg, char *error, char *seps);
char		*ft_get_prompt(bool err);
void		ft_print_logo(void);

// syntax_check_utils.c
bool		finished_by_meta(char *str);
bool		is_brace_well_formatted(char *str);
bool		has_semicolon(char *str);
int			is_well_formatted(char *str);

// unlink_hd.c
void		unlink_heredoc(t_skibidi *shell, t_token *token);

#endif
