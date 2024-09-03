#include <stdio.h>
#include <stdlib.h>
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

// int	main(int ac, char **av)
// {
// 	int		i;
// 	char	*old;
// 	char	*input;

// 	i = 1;
// 	input = ft_strjoin(av[i], " ");
// 	i++;
// 	while (i < ac)
// 	{
// 		old = input;
// 		input = ft_strjoin(old, av[i]);
// 		free(old);
// 		old = input;
// 		input = ft_strjoin(old, " ");
// 		free(old);
// 		i++;
// 	}
// 	printf("%s\n", input);
// 	free(input);
// }

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (c);
	}
	else
		return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*exp_positional_param(char *str)
{
	int		i;
	int		j;
	int		nb_pos_param;
	char	*expanded_str;

	i = 0;
	nb_pos_param = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && ft_isdigit(str[i + 1]) != 0)
		{
			nb_pos_param++;
			i = i + 2;
			continue;
		}
		i++;
	}
	expanded_str = malloc(1 + (ft_strlen(str) - (2 * nb_pos_param)));
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && ft_isdigit(str[i + 1]) != 0)
		{
			i = i + 2;
			continue;
		}
		expanded_str[j] = str[i];
		j++;
		i++;
	}
	expanded_str[j] = '\0';
	return (expanded_str);
}

int	main(int ac, char **av)
{
	printf("%s\n", "$37 $1okokokok $ok$1ok");

	printf("%s\n", exp_positional_param("$37 $1okokokok $ok$1ok"));
}
