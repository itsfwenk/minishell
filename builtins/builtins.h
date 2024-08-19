/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:17:55 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 16:06:07 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				deleted;
	struct s_env	*next;
}	t_env;

// utils
int		check_key(char *key);
t_env	*get_env(t_env *env, char *key);
t_env	*add_env(t_env **env, char *key, char *value);
void	del_env(t_env **env, char *key);
void	free_env(t_env *env);

int		ft_pwd(void);
int		ft_env(t_env *env);
int		ft_unset(t_env **env, char **keys);
int		ft_export(t_env **env, char **args);

#endif
