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
int main (int ac, char *argv[], char *envp[])
{
	char **string;
	char *prompt = "Ishell#$ ";
	char *lineptr;
	size_t n = 20, pah = 10;
	ssize_t n_char;
	char *fchk;

	if (ac > 1)
		argv[1] = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf ("%s", prompt);
		lineptr = malloc(sizeof(char) * n);
		n_char = getline(&lineptr, &n, stdin);
		if (n_char == -1)
		{
			free(lineptr);
			exit(EXIT_FAILURE);
		}
		if (lineptr[0] != '\n')
		{
			string = token_cmd(lineptr);
			if (strcmp("exit", string[0]) == 0)
				break;
			if (strcmp("exit", string[0]) == 0)
				exit_shell(EXIT_SUCCESS);
			fchk = fcheck(string[0]);
			if (fchk != NULL)
				string[0] = fchk;
			pah = pcheck(string[0]);
			if (pah == 1)
				excecmd(string, envp);
			else if (fchk == NULL && pah == 0)
				printf("./shell: No such file or directory\n");
			free(string);
		}
		free(lineptr);
	}
	free(fchk);

	return (0);
}
