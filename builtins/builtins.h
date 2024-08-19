/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:17:55 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 12:46:06 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../libft/libft.h"
# include "./utils/utils.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	size_t			index;
	struct s_env	*next;
}	t_env;

int	ft_pwd(void);
int	ft_env(t_env *env);

#endif
