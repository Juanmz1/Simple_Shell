#include "shell.h"
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * excecmd - execute a command and fork the process
 * @arrs: Arrays of string gotten from the command line
 * Return: void
 */
#define MAX_COMMANDS 10
void excecmd(char **arrs)
{
	pid_t pid;
	int status;
	char *cmd_act = NULL;
	char *cmd_envp = NULL;

	pid = fork();
	if (pid == -1)
	{
		perror("Error: fork issue");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		cmd_envp = print_env(arrs[0]);
		cmd_act = togetenv(arrs[0]);
		if (execve(cmd_act, arrs, NULL) == -1)
		{
			perror("./shell: No such file or directory\n");
		}
		if (execve(cmd_envp, arrs, NULL) == -1)
		{
			perror("./shell: No such file or directory\n");
		}
	}
	else
	{
		wait(&status);
	}
}
