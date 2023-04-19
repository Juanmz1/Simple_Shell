#include "shell.h"
/**
 * excecmd - execute a command
 * @argv: argument pass
 * Return: void
 */
void excecmd(char **argv)
{
	char *cmd = NULL;

	if (argv)
	{
		cmd = argv[0];

		if (execve(cmd, argv, NULL) == -1)
		{
			perror("Error:");
		};
	}
}
