

#include "lexer.h"

int	main(int ac, char **av)
{
	int			i;
	int			j;
	char		*old;
	char		*input;
	t_token		*tokens;
	t_token		*current_token;
	t_string	*current_tstring;

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
	tokens = ft_lexer(input);
	current_token = tokens;
	while (current_token != NULL)
	{
		current_tstring = current_token->tstring;
		j = 1;
		while (current_tstring != NULL)
		{
			printf("tstring content %d : %s\n", j, current_tstring->str);
			j++;
		}
		printf("type %d\n", current_token->type);
	}
	free(input);
}
