/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:34:50 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/03 18:52:27 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

// Enums
typedef enum e_side			t_side;
typedef enum e_type			t_type;

// Structures
typedef struct s_pid		t_pid;
typedef struct s_env		t_env;
typedef struct s_string		t_string;
typedef struct s_token		t_token;
typedef struct s_kibidi		t_skibidi;
typedef struct stat			t_stat;

// bi_checkers.c
bool	check_key(char *key);
bool	is_builtin(char	*cmd);

// bi_env.c
t_env	*get_env(t_env *env, char *key);
t_env	*add_env(t_env **env, char *key, char *value);
void	unset_env(t_env *env, char *key);

// ft_cd.c
int		ft_cd(t_env	*env, char **dir_path);

// ft_echo.c
int		ft_echo(char **echo_arg);

// ft_env.c
int		ft_env(t_env *env, char **args);

// ft_exit.c
int		ft_exit(t_skibidi *shell, char **args);

// ft_export.c
int		ft_export(t_skibidi *shell, char **args);

// ft_pwd.c
int		ft_pwd(char **args);

// ft_unset.c
int		ft_unset(t_env *env, char **keys);

#endif
