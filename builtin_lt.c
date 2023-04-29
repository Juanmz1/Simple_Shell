#include "shell.h"

/**
 * builtin_lt - search for match and execute the associate builtin
 * @data: access to the program file
 * Retuen: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 */
int builtin_lt(file_of_prog *data)
{
	int ite;
	builtins opt[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias}
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

	for (ite = 0; opt[ite].builtin != NULL; ite++)
	{
		if (str_cmp(opt[ite].builtin, data->com_name, 0))
		{
			return(opt[ite].function(data));
		}
	}
	return (-1);
}
