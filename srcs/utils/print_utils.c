/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 00:12:23 by mel-habi          #+#    #+#             */
/*   Updated: 2024/10/07 13:32:19 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skibidishell.h"

void	ft_print_color(char *msg, char *color)
{
	printf("%s%s%s", color, msg, END_COLOR);
}

void	ft_print_error(char *cmd, char *arg, char *error, char *seps)
{
	if (!cmd && seps)
		ft_dprintf(2, "%s skibidi bop no no no: %s %c%s%c%s",
			WARNING_EMOJI BOLD YELLOW, error, seps[0], \
			arg, seps[1], END_COLOR);
	else if (!arg)
		ft_dprintf(2, "%s skibidi bop no no no: %s: %s%s",
			WARNING_EMOJI BOLD YELLOW, cmd, error, \
			END_COLOR);
	else
		ft_dprintf(2, "%s skibidi bop no no no: %s: %c%s%c: %s%s",
			WARNING_EMOJI BOLD YELLOW, cmd, \
			seps[0], arg, seps[1], error, END_COLOR);
	ft_dprintf(2, "\n");
}

char	*ft_get_prompt(bool err)
{
	if (err)
		return (ERROR_EMOJI BOLD RED PROMPT END_COLOR);
	return (SUCCESS_EMOJI BOLD GREEN PROMPT END_COLOR);
}

void	ft_print_logo(void)
{
	ft_print_color("⣿⣫⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ S\n", BOLD CYAN);
	ft_print_color("⣶⣿⣿⣿⣿⣿⠿⠛⠉⠀⠀⠀⠀⠀⠀⠉⠙⠻⣿⣿⣿⣿⣿⣿ K  B\n", BLUE);
	ft_print_color("⣿⣿⣿⣿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠹⣿⣿⣿⣿ I  y\n", BOLD CYAN);
	ft_print_color("⣿⣿⡿⠃⠀⠀⣀⣀⣤⣄⣤⣤⣤⣦⣤⣤⣴⣖⣢⠀⠈⢻⣿⣿ B\n", BLUE);
	ft_print_color("⣾⣿⠁⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡼⢆⠀⠀⠈⣿⣿ I  f\n", BOLD CYAN);
	ft_print_color("⣿⣿⠀⠀⣸⣿⣿⣿⣿⠿⠟⠻⠛⠻⠿⠿⠿⣿⣇⠂⠀⠀⣿⣿ D  l\n", BLUE);
	ft_print_color("⣿⣿⡀⠀⡏⠛⠋⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⣿ I  i\n", BOLD CYAN);
	ft_print_color("⢿⡟⢧⠀⣇⠀⠀⢠⠴⡀⠀⢀⣦⠀⠀⢀⠂⡄⠀⢀⡂⠈⢸⣿\n", BLUE);
	ft_print_color("⣦⣿⠀⠀⣿⣷⣤⣽⣞⣁⣠⣾⣿⢗⣠⣬⠩⠴⢾⠛⠀⡀⢸⣿ S  &\n", BOLD CYAN);
	ft_print_color("⣿⣿⡆⠐⢙⠛⠙⠛⢻⠼⣿⣿⣿⡋⠤⠉⡰⠁⠀⠀⠀⠄⣾⣿ H\n", BLUE);
	ft_print_color("⡇⠞⢲⡌⠀⠌⠒⢈⢛⣢⠛⠾⠿⠅⠀⡄⡁⠒⠀⠀⢀⣼⣿⣿ E  m\n", BOLD CYAN);
	ft_print_color("⢹⣾⣿⣿⣇⠈⠄⡀⠀⠉⠃⠀⠀⠀⠐⠀⠀⠀⠀⠀⣸⣿⣿⣿ L  e\n", BLUE);
	ft_print_color("⡃⣿⣿⣿⣿⡀⠉⠽⡀⠀⠰⡦⣷⣦⡄⠀⠀⠀⠀⢠⣿⣿⣿⣿ L  l\n", BOLD CYAN);
	ft_print_color("⡙⠸⣿⣿⣿⣧⠀⠀⠙⢆⡀⠉⠉⠉⡀⠀⠀⠀⠀⣾⣿⣿⣿⣿    -\n", BLUE);
	ft_print_color("⠈⢁⠈⢿⣿⣿⠀⠀⠀⠀⠹⣷⠿⠷⠀⠀⠀⠀⢸⣿⣿⣿⣿⣿ v  h\n", BOLD CYAN);
	ft_print_color("⣊⣤⣤⣤⣤⣄⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣈⣉⣉⣉⣁⣀ 1  a\n", BLUE);
	ft_print_color("⣿⣿⣿⣿⣿⣿⣷⣶⣶⣶⣶⣶⣶⣶⣶⣶⣶⣾⣿⣿⣿⣿⣿⣿ .  b\n", BOLD CYAN);
	ft_print_color("⣿⣿⣿⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣭⣽⣯⣿⣷⣿⣶⣶ 🚽 i\n\n", BLUE);
	ft_print_color("🎶 Skibidi Bop Yes Yes Yes 🎶\n\n", BOLD YELLOW);
}
