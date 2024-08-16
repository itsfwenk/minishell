/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <fli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:25:25 by fli               #+#    #+#             */
/*   Updated: 2024/06/19 17:07:35 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (!(s[i] == c)
			&& ((s[i + 1] == c) || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static char	*ft_splitdup(int start, int end, char const *s)
{
	int		i;
	char	*word;

	word = malloc((1 + (end - start)) * sizeof(char));
	if (word == NULL)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i++] = s[start++];
	}
	word[i] = '\0';
	return (word);
}

static int	ft_next(int start, char const *s, char c)
{
	while (!(s[start] == c) && s[start])
	{
		start++;
	}
	return (start);
}

static void	ft_free_all(char **split, int size)
{
	int	j;

	j = 0;
	while (j < size)
		free(split[j++]);
	free (split);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		start;
	char	**split;

	start = 0;
	split = malloc((1 + ft_count(s, c)) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	while (i < ft_count(s, c))
	{
		if (start != ft_next(start, s, c))
		{
			split[i++] = ft_splitdup(start, ft_next(start, s, c), s);
			if (split[i - 1] == NULL)
			{
				ft_free_all(split, i - 1);
				return (NULL);
			}
		}
		start = ft_next(start, s, c) + 1;
	}
	split[i] = 0;
	return (split);
}

/* #include <stdio.h>
int	main(int argc, char **argv)
{
	(void) argc;
	int	i = 0;
	char **tab = ft_split((char const *)argv[1], '*');
	while (tab[i] != NULL)
	{
		printf("%s\n", tab[i]);
		i++;
	}
 	int	x = 0;
	while (tab[x] != NULL)
	{
		free (tab[x]);
		x++;
	}
	free (tab);
}*/
