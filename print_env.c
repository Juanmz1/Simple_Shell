#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

extern char **environ;
#define MAX_CMD 256

/* print_env - an in built command to print the env variables
 * @cmd: command to access the string inputed
 * Return: return a pointer to a char
*/
char *print_env(char *cmd)
{
	char **envp = environ;
	int i = 0;
	size_t n = 0;
	ssize_t n_read;
	
	cmd = malloc(sizeof(char) * 64);
	n_read = getline(&cmd, &n, stdin);

	if (n_read == -1)
	{
		free(cmd);
		return (NULL);
	}
	cmd[strcspn(cmd, "\n")] = '\0';
	if (strcmp(cmd, "envp") == 0)
	{
		printf("Environment Variables\n");
		for (i = 0; envp[i] != NULL; i++)
		{
			printf("%s\n", envp[i]);
		}
	}
	free(cmd);
	
	return (NULL);
}

