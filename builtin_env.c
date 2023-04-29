#include "shell.h"

/**
 * builtin_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_env(file_of_prog *data)
{
	int i;
	char cpname[50] = {'\0'}
	char *var_copy = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_env(data);
	else
	{
		for (i = 0; data->tokens[1][i]; i++)
		{/* checks if exists a char = */
			if (data->tokens[1][i] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				var_copy = str_dup(env_get(cpname, data));
				if (var_copy != NULL)
					env_set(cpname, data->tokens[1] + i + 1, data);

				/* print the environ */
				print_env(data);
				if (env_get(cpname, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					my_printf(data->tokens[1]);
					my_printf("\n");
				}
				else
				{/* returns the old value of the var*/
					env_set(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->tokens[1][i];
		}
		errno = 2;
		perror(data->com_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - set the env
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_set_env(file_of_prog *data)
{
	/* validate args */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->com_name);
		return (5);
	}

	env_set(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - ..
 * @data: struct for the program's data'
 * Return: ..
 */
int builtin_unset_env(file_of_prog *data)
{
	/* validate args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->com_name);
		return (5);
	}
	env_rem(data->tokens[1], data);

	return (0);
}
