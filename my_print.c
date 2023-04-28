#include "shell.h"

/**
 * my_printf - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_printf(char *string)
{
	return (write(STDOUT_FILENO, string, str_len(string)));
}
/**
 * my_printf_err - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_printf_err(char *string)
{
	return (write(STDERR_FILENO, string, str_len(string)));
}

/**
 * my_printf_error - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_printf_error(int errorcode, file_of_prog *data)
{
	char n_as_string[10] = {'\0'};

	long_str((long) data->exec_count, n_as_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		my_printf_e(data->prog_name);
		my_printf_e(": ");
		my_printf_e(n_as_string);
		my_printf_e(": ");
		my_printf_e(data->tokens[0]);
		if (errorcode == 2)
			my_printf_e(": Illegal number: ");
		else
			my_printf_e(": can't cd to ");
		my_printf_e(data->tokens[1]);
		my_printf_e("\n");
	}
	else if (errorcode == 127)
	{
		my_printf_e(data->prog_name);
		my_printf_e(": ");
		my_printf_e(n_as_string);
		my_printf_e(": ");
		my_printf_e(data->com_name);
		my_printf_e(": not found\n");
	}
	else if (errorcode == 126)
	{
		my_printf_e(data->prog_name);
		my_printf_e(": ");
		my_printf_e(n_as_string);
		my_printf_e(": ");
		my_printf_e(data->com_name);
		my_printf_e(": Permission denied\n");
	}
	return (0);
}
