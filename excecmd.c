#include "shell.h"
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * excecmd - execute a command and fork the process
 * @arrs: Arrays of string gotten from the command line
 * @envp: Environment variable from the parent
 * Return: void
 */
#define MAX_COMMANDS 10
void excecmd(char **arrs, char *envp[])
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: fork issue");
		return;
	}
	if (pid == 0)
	{
		if (execve(arrs[0], arrs, envp) == -1)
		{
			perror("./shell: No such file or directory\n");
		}
	}
	else
	{
		wait(&status);
	}
}
