#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

/**
 * togetenv - function to get the path of the environment variable
 * @cmd: command to access the path
 * Return: return a pointer to a char
 */
char *togetenv(char *cmd)
{
	char *path, *path_cpy, *token_path;
	int cmd_len, direc_len;
	char *file;
	struct stat buff;

	path = getenv("PATH");
	if (path)
	{
		path_cpy = strdup(path);
		cmd_len = strlen(cmd);
		token_path = strtok(path_cpy, ":");
		
		while (token_path != NULL)
		{
			direc_len = strlen(token_path);
			file = malloc(sizeof(cmd_len + direc_len + 2));
			strcpy(file, token_path);
			strcat(file, "/");
			strcat(file, cmd);
			strcat(file, "\0");
			
			if (stat(file, &buff) == 0)
			{
				free(path_cpy);
				return (file);
			}
			else
			{
				free(file);
				token_path =strtok(NULL, ":");
			}
		}
		free(path_cpy);
		
		if (stat(cmd, &buff) == 0)
		{
			return (cmd);
		}
		return (NULL);
	}
	return (NULL);
}
