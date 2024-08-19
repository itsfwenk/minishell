/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-habi <mel-habi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:23:12 by mel-habi          #+#    #+#             */
/*   Updated: 2024/08/19 17:22:24 by mel-habi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_charset(char c, char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);	
}

static size_t	count_words(char const *s, char *c)
{
	size_t	words;
	size_t	i;
	size_t	in;

	words = 0;
	i = 0;
	in = 0;
	while (s[i])
	{
		if (!in_charset(s[i], c) && !in)
		{
			words++;
			in = 1;
		}
		else if (in_charset(s[i], c) && in)
			in = 0;
		i++;
	}
	return (words);
}

static char	*fill_word(char const *s, char *c)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (s[len] && !in_charset(s[len], c))
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

char	**free_all(char **result)
{
	size_t	i;

	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char *c)
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
			while (in_charset(s[j], c))
				j++;
			result[i] = fill_word(s + j, c);
			if (!result[i])
				return (free_all(result));
			j += ft_strlen(result[i]);
			i++;
		}
	}
	return (result);
}
