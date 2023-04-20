#include "shell.h"

/**
 * pcheck - function to check if the string has the path "/bin/"
 * @cmd: the string to carry out the check
 * Return: fail return 0 and pass return 1
 */
int pcheck(char *cmd)
{
	char *path = "/bin/";
	char *lineptr, *lin;
	int i = 0, j = 0;

	lineptr = malloc(sizeof(char) * 64);
	if (lineptr == NULL)
	{
		free(lineptr);
		exit(EXIT_FAILURE);
	}
	while (path[i] != '\0')
	{
		if (path[i] != cmd[i])
		{
			free(lineptr);
			return (0);
		}
		i++;
	}
	while (cmd[i] != '\0')
	{
		lineptr[j] = cmd[i];
		j++;
		i++;
	}
	lineptr = '\0';
	lin = fcheck(lineptr);
	if (lin != NULL)
	{
		free(lineptr);
		return (1);
	}
	return (0);
}
