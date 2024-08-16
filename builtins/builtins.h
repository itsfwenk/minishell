/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 18:17:55 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/16 19:50:13 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
#include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				index;
	struct s_env	*next;
}	t_env;

int	ft_pwd(void);

#endif
