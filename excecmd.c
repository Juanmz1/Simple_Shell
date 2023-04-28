#include "shell.h"
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/**
 * excecmd - execute a command and fork the process
 * @data: Acess to the program file
 * Return: if success return 0 else return -1
 */
int excecmd(file_of_prog *data)
{
	pid_t pidd;
	int status;
	int val = 0;
	
	val = builtin_lt(data);
	if (val != -1)
		return (val);
	val = find_prog(data);
	if (val)
	{
		return (val);
	}
	else
	{
		pidd = fork();
		if (pidd == -1)
		{
			perror(data->com_name);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			val = execve(data->tokens[0], data->tokens, data->env);
			if (val == -1)
			{
				perror(data->com_name);
				exit(EXIT_FAILURE);
			}
		}
		else 
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
