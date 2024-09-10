#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

# define FALSE 0
# define TRUE 1
// int main()
// {
// 	DIR		*directory;
// 	struct	dirent *read_return;

// 	directory = opendir(".");
// 	read_return = readdir(directory);
// 	while (read_return != NULL)
// 	{
// 		printf("%s\n", read_return->d_name);
// 		read_return = readdir(directory);
// 	}
// 	closedir(directory);
// }

int	check_filename(char *current, char *read_return, int i, int j)
{
	int	k;

	k = 0;
	while (current[i + k] != '\0')
	{
		if (current[i + k] == '*')
		{
			i++;
			if (current[i] == '\0')
				return (TRUE);
			while (current[i + k] != '\0' && read_return[j + k] != '\0'
				&& current[i] != read_return[j])
			{
				if (current[i] == '*')
					return (check_filename(current, read_return, i + k, j + k));
				j++;
			}
		}
		while (current[i + k] != '\0' && read_return[j + k] != '\0')
		{
			if (current[i + k] == '*')
			{
				if (check_filename(current, read_return, i + k, j + k) == TRUE)
					return (TRUE);
				j++;
				k = 0;
			}
			else if (current[i + k] == read_return[j + k])
				k++;
			else
			{
				k = 0;
				j++;
			}
		}
		if ((current[i + k] != '\0' || read_return[j + k] != '\0') && current[i + k] != '*')
			return (FALSE);
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	int	function_return;
	char	*str = argv[1];
	char	*filename = argv[2];

	function_return = check_filename(str, filename, 0, 0);
	if (function_return == TRUE)
		printf("%s\n", "TRUE");
	else
		printf("%s\n", "FALSE");
}
