#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * token_cmd - to separate the arrays of strings
 * @cmd: commands pass
 * Return: Arrays of string
 */
char **token_cmd(char *lineptr_cpy)
{
	char **argv;
	char *token;
	int token_num = 0, i = 0;

	argv = malloc(sizeof(char *) * 8);
	if (argv == NULL)
	{
		perror("can't allocate space");
		exit(EXIT_FAILURE);
	}
	token = strtok(lineptr_cpy, " ");
	while (token != NULL)
	{
		while (token[token_num])
		{
			if (token[token_num] == '\n')
			{
				token[token_num] = '\0';
			}
			token_num++;
		}
		argv[i] = malloc(sizeof(char) * token_num);
		if (argv[i] == NULL)
		{
			perror("memory allocation error");
			exit(EXIT_FAILURE);
		}
		strcpy(argv[i], token);
		i++;
		token_num = 0;
		token = strtok(NULL, " ");
	}
	argv[i] = NULL;

	return (argv);
}


