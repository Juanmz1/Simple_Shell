#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int print_alias(file_of_prog *data, char *alias)
{
	int i, j, alias_length;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		alias_length = str_len(alias);
		for (i = 0; data->alias_lt[i]; i++)
		{
			if (!alias || (str_cmp(data->alias_lt[i], alias, alias_length)
				&&	data->alias_lt[i][alias_length] == '='))
			{
				for (j = 0; data->alias_lt[i][j]; j++)
				{
					buffer[j] = data->alias_lt[i][j];
					if (data->alias_lt[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buff_add(buffer, "'");
				buff_add(buffer, data->alias_lt[i] + j + 1);
				buff_add(buffer, "'\n");
				my_printf(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(file_of_prog *data, char *name)
{
	int i, alias_length;

	/* validate the arguments */
	if (name == NULL || data->alias_lt == NULL)
		return (NULL);

	alias_length = str_len(name);

	for (i = 0; data->alias_lt[i]; i++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_cmp(name, data->alias_lt[i], alias_length) &&
			data->alias_lt[i][alias_length] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_lt[i] + alias_length + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, file_of_prog *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_lt == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; data->alias_lt[j]; j++)
		if (str_cmp(buffer, data->alias_lt[j], i) &&
			data->alias_lt[j][i] == '=')
		{/* if the alias alredy exist */
			free(data->alias_lt[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		buff_add(buffer, "=");
		buff_add(buffer, temp);
		data->alias_lt[j] = str_dup(buffer);
	}
	else /* if the alias does not exist */
		data->alias_lt[j] = str_dup(alias_string);
	return (0);
}
