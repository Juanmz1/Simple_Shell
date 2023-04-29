#include "shell.h"

/**
 * free_recur_data - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_recur_data(file_of_prog *data)
{
	if (data->tokens)
		free_arr_pointers(data->tokens);
	if (data->inp_line)
		free(data->inp_line);
	if (data->com_name)
		free(data->com_name);

	data->inp_line = NULL;
	data->com_name = NULL;
	data->tokens = NULL;
}

/**
 * free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void free_all_data(file_of_prog *data)
{
	if (data->file_des != 0)
	{
		if (close(data->file_des))
			perror(data->prog_name);
	}
	free_recur_data(data);
	free_arr_pointers(data->env);
	free_arr_pointers(data->alias_lt);
}

/**
 * free_arr_pointers - frees each pointer of an array of pointers and the
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void free_arr_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
