#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/**
 * token - to separate the arrays of strings
 * @data: a pointer to the program data
 * Return: Arrays of string
 */
void token(file_of_prog *data)
{
	char *deli = "\t";
	int count = 2, i, len, j;

	len = str_len(data->inp_line);
	if (len)
	{
		if(data->inp_line[len - 1] == '\n')
			data->inp_line[len - 1] = '\0';
	}
	for (i = 0; data->inp_line[i]; i++)
	{
		for (j = 0; deli[i]; j++)
		{
			if (data->inp_line[i] == deli[j])
			{
				count++;
			}
		}
		data->tokens = malloc(count * sizeof(char *));
		if (data->tokens == NULL)
		{
			perror(data->prog_name);
			exit(errno);
		}
		i = 0;
		data->tokens[i] = str_dup(my_strtok(data->inp_line, deli));
		data->com_name = str_dup(data->tokens[0]);
		while (data->tokens[i++])
		{
			data->tokens[i] = str_dup(my_strtok(NULL, deli));
		}
	}
}
