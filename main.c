#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point
 * @ac: arg count
 * @argv: arg vector
 * @envp: array of environment variables
 * Return: 0 
*/
#define MAX_COMMANDS 10
int main (int ac, char *argv[])
{
	char **string;
	char *prompt = "Ishell#$ ";
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t n_char;

	if (ac > 1)
		argv[1] = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("%s", prompt);
		lineptr = malloc(sizeof(char) * n);
		n_char = my_getline(&lineptr, &n, stdin);
		if (n_char == -1)
		{
			printf("EXITING SHELL");
			return (-1);
		}
		if (*lineptr != '\n')
		{
			string = token_cmd(lineptr);
			if (strcmp("exit",string[0]) == 0)
				break;
			if (strcmp("exit", string[0]) == 0)
				exit_shell(EXIT_SUCCESS);
			excecmd(string);
		}
	}
	free(lineptr);
	free(string);

	return (0);
}
