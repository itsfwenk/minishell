/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:23:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/05/23 15:15:10 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	size_t	i;
	size_t	in;

	words = 0;
	i = 0;
	in = 0;
	while (s[i])
	{
		if (s[i] != c && !in)
		{
			words++;
			in = 1;
		}
		else if (s[i] == c && in)
			in = 0;
		i++;
	}
	return (words);
}

static char	*fill_word(char const *s, char c)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (result)
	{
		while (i < len)
		{
			result[i] = s[i];
			i++;
		}
	}
	return (result);
}

static char	**free_all(char **result, size_t last_i)
{
	size_t	i;

	i = 0;
	while (i < last_i)
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	size_t	i;
	size_t	j;
	char	**result;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	i = 0;
	j = 0;
	result = (char **)ft_calloc(words + 1, sizeof(char *));
	if (result)
	{
		while (i < words)
		{
			while (s[j] == c)
				j++;
			result[i] = fill_word(s + j, c);
			if (!result[i])
				return (free_all(result, i));
			j += ft_strlen(result[i]);
			i++;
		}
	}
	return (result);
}
