#include "shell.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * fcheck - function to check if the system command exist
 * @cmd: checking string
 * Return: append the path or NULL
 */
char *fcheck(char *cmd)
{
	DIR *direc = opendir("/bin/");
	char *tmp, *caten;
	struct dirent end;
	
	if (direc == NULL)
		return (NULL);
	end = readdir(direc);
	while(end != NULL)
	{
		tmp = end->d_name;
		if (strcmp(tmp, cmd) == 0)
		{
			caten = strcat("/bin/", cmd);
			closedir(direc);
			return (caten);
		}
		end = readdir(direc);
	}
	closedir(direc);
	return (NULL);
}
