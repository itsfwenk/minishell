/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:35:28 by fli               #+#    #+#             */
/*   Updated: 2024/05/24 10:24:25 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		else
			i++;
	}
	return (0);
}

static int	ft_trimleft(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (ft_checkset(s1[start], set) == 1)
		start++;
	return (start);
}

static int	ft_trimright(char const *s1, char const *set)
{
	int	end;

	end = ft_strlen(s1);
	while (ft_checkset(s1[end - 1], set) == 1)
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trim;

	start = ft_trimleft(s1, set);
	end = ft_trimright(s1, set);
	if (end - start < 0)
		trim = malloc(1 * sizeof(char));
	else
		trim = malloc((end - start + 1) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, &s1[start], (end - start + 1));
	return (trim);
}

/* #include <stdio.h>
int	main()
{
		char const s[45] = "   xxx   xxx";
		//char const set[5] = "";

		printf("%s\n", ft_strtrim(s, " x"));
}*/
