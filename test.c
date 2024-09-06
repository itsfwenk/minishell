#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
	DIR		*directory;
	struct	dirent *read_return;

	directory = opendir(".");
	read_return = readdir(directory);
	while (read_return != NULL)
	{
		printf("%s\n", read_return->d_name);
		read_return = readdir(directory);
	}
	closedir(directory);
}
