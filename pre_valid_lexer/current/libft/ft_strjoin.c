/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fli <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:31:25 by fli               #+#    #+#             */
/*   Updated: 2024/05/23 16:57:06 by fli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		tot;
	char	*joined;

	tot = ft_strlen(s1) + ft_strlen(s2) + 1;
	joined = malloc((tot) * sizeof(char));
	if (joined == NULL)
		return (NULL);
	ft_strlcpy(joined, s1, ft_strlen(s1) + 1);
	ft_strlcat(joined, s2, tot);
	return (joined);
}

/* #include <stdio.h>
int	main()
{
	char const s1[500] = "lorem ipsum";
	char const s2[200] = "dolor sit amet";
	char *res = ft_strjoin(s1, s2);
	printf("%s\n", res);
}*/
