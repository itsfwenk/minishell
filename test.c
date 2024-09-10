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

// int	check_filename(char *current, char *read_return, int i, int j)
// {
// 	if (current[i] == '\0' && read_return[j] == '\0')
// 		return (TRUE);
// 	if (current[i] == '*')
// 	{
// 		if (check_filename(current, read_return, i + 1, j) == TRUE);
// 			return (TRUE);
// 		return (check_filename(current, read_return, i, j + 1));
// 	}
// 	if (current[i] == read_return[j])
// 		return (check_filename(current, read_return, i + 1, j + 1));
// 	return (FALSE);
// }

int check_filename(char *wc, char *filename, int i, int j)
{
	while (wc[i] != '\0')
	{
		if (wc[i] == '*')
		{
			i++;
			if (wc[i] == '\0')
				return (TRUE);
			while (filename[j] != '\0')
			{
				if (check_filename(wc, filename, i, j) == TRUE)
					return (TRUE);
				j++;
			}
			return (FALSE);
		}
		else if (wc[i] != filename[j])
			return (FALSE);
		i++;
		j++;
	}
	return (filename[j] == '\0');
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
