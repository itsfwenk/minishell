/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:39:54 by mel-habi          #+#    #+#             */
/*   Updated: 2024/09/17 17:36:00 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_UTILS_H
# define MS_UTILS_H

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
# define ERROR_EMOJI "😿"

typedef struct s_kibidi
{
	t_env	*env;
	t_token	*tokens;
	t_token	*tree;
}	t_skibidi;

void	ft_print_color(char *msg, char *color);
void	ft_print_error(char *cmd, char *arg, char *error, char *seps);
char	*ft_get_prompt(int err);
void	ft_free_clean(t_skibidi *skibidishell);
int		is_well_formated(char *str);
int		finished_by_meta(char *str);
int		is_brace_well_formated(char *str);
int		has_semicolon(char *str);

#endif
