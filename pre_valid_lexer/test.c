#include <stdio.h>
# include "libft.h"

// int main(int ac, char **av)
// {
//   int i;
//   i = 0;
//   while (i < ac)
//   {
//     printf("%s\n", av[i]);
//     i++;
//   }
// }

int	main(int ac, char **av)
{
	int		i;
	char	*old;
	char	*input;

	i = 1;
	input = ft_strjoin(av[i], " ");
	i++;
	while (i < ac)
	{
		old = input;
		input = ft_strjoin(old, av[i]);
		free(old);
		old = input;
		input = ft_strjoin(old, " ");
		free(old);
		i++;
	}
	printf("%s\n", input);
	free(input);
}
