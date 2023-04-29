#include "shell.h"

/**
 * builtin_exit - exit of the program with the status
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_exit(file_of_prog *data)
{
	int i;

	if (data->tokens[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (i = 0; data->tokens[1][i]; i++)
			if ((data->tokens[1][i] < '0' || data->tokens[1][i] > '9')
				&& data->tokens[1][i] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = my_atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - change the current directory
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_cd(file_of_prog *data)
{
	char *dir_home = env_get("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int error_code = 0;

	if (data->tokens[1])
	{
		if (str_cmp(data->tokens[1], "-", 0))
		{
			dir_old = env_get("OLDPWD", data);
			if (dir_old)
				error_code = set_wk_dir(data, dir_old);
			my_printf(env_get("PWD", data));
			my_printf("\n");

			return (error_code);
		}
		else
		{
			return (set_wk_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (set_wk_dir(data, dir_home));
	}
	return (0);
}

/**
 * set_wk_dir - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_wk_dir(file_of_prog *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!str_cmp(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set("PWD", new_dir, data);
	}
	env_set("OLDPWD", old_dir, data);
	return (0);
}

/**
 * builtin_help - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_help(file_of_prog *data)
{
	int i, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		my_printf(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->com_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (i = 0; mensajes[i]; i++)
	{
		length = str_len(data->tokens[1]);
		if (str_cmp(data->tokens[1], mensajes[i], length))
		{
			my_printf(mensajes[i] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->com_name);
	return (0);
}

/**
 * builtin_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int builtin_alias(file_of_prog *data)
{
	int i = 0;

	/* if there are no arguments, print all environment */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{/* if there are arguments, set or print each env variable*/
		if (count_char(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}
