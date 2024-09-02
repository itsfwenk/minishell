

#include "lexer.h"

// int	main(int ac, char **av)
// {
// 	int			i;
// 	int			j;
// 	int			nodenb;
// 	char		*old;
// 	char		*input;
// 	t_token		*tokens;
// 	t_token		*current_token;
// 	t_string	*current_tstring;

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
// 	tokens = ft_lexer(input);
// 	current_token = tokens;
// 	nodenb = 1;
// 	while (current_token != NULL)
// 	{
// 		printf("NODE NUMBER %d\n", nodenb);
// 		current_tstring = current_token->tstring;
// 		j = 1;
// 		while (current_tstring != NULL)
// 		{
// 			printf("tstring content %d : %s\n", j, current_tstring->str);
// 			current_tstring = current_tstring->next;
// 			j++;
// 		}
// 		printf("type %d\n", current_token->type);
// 		current_token = current_token->next;
// 		nodenb++;
// 	}
// 	lx_deltokens(&tokens);
// 	free(input);
// }

void	print_token(int token_type)
{
	if (token_type == PIPE)
			printf("PIPE");
	if (token_type == OR)
			printf("OR");
	if (token_type == APD_OUT_REDIR)
		printf("APD_OUT_REDIR");
	if (token_type == OUT_REDIR)
		printf("OUT_REDIR");
	if (token_type == HERE_DOC)
		printf("HERE_DOC");
	if (token_type == IN_REDIR)
		printf("IN_REDIR");
	if (token_type == AND)
		printf("AND");
	if (token_type == STR)
		printf("STR");
	if (token_type == HD_LIMITER)
		printf("HD_LIMITER");
	if (token_type == FILENAME)
		printf("FILENAME");
	if (token_type == PAR_STR)
		printf("PAR_STR");
}

void	print_subshell(t_token *current_token)
{
	int		i;
	int		j;
	t_token	*in_token;
	t_string	*current_tstring;

	if (current_token->type == PAR_STR)
	{
		printf("	in subshell\n");
		in_token = current_token->sub_shell;
		i = 1;
		while (in_token != NULL)
		{
			print_subshell(in_token);
			j = 1;
			printf("	in subshell NODE NUMBER %d\n", i);
			current_tstring = in_token->tstring;
			while (current_tstring != NULL)
			{
				printf("	in subshell tstring content %d : %s\n", j, current_tstring->str);
				j++;
				current_tstring = current_tstring->next;
			}
			i++;
			print_token(in_token->type);
			printf("\n");
			printf("\n");
			in_token = in_token->next;
		}
	}
}

int	main()
{
	int			j;
	int			nodenb;
	t_token		*tokens;
	t_token		*current_token;
	t_string	*current_tstring;

	char *input = "(ls | cat) | echo ok";
	printf("%s\n", input);
	tokens = ft_lexer(input);
	printf("tokens created\n");
	check_syntax(tokens);
	current_token = tokens;
	nodenb = 1;
	while (current_token != NULL)
	{
		printf("NODE NUMBER %d\n", nodenb);
		printf("full string : %s\n", current_token->full_string);
		current_tstring = current_token->tstring;
		j = 1;
		while (current_tstring != NULL)
		{
			printf("tstring content %d : %s\n", j, current_tstring->str);
			current_tstring = current_tstring->next;
			j++;
		}
		print_token(current_token->type);
		printf("\n");
		printf("\n");
		print_subshell(current_token);
		printf("\n");
		printf("\n");
		current_token = current_token->next;
		nodenb++;
	}
	lx_deltokens(&tokens);
}
