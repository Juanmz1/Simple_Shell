#include "shell.h"
/**
 * excecmd - execute a command
 * @argv: argument pass
 * Return: void
 */
#define MAX_COMMANDS 10
void excecmd(char *const argv[], char *const envp[])
{
	char *cmd[MAX_COMMANDS];
	char *const argv[MAX_COMMANDS];


	if (argv)
	{
		cmd = argv[0];

		if (execve(cmd, argv, NULL) == -1)
		{
			perror("Error:");
		};
	}
}
