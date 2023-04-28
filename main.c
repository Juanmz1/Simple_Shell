#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * main - entry point
 * @argc: arg count
 * @argv: arg vector
 * @env: number of value recieved
 * Return: 0
*/

int main(int argc, char *argv[], char **env)
{
	File_of_prog data_struct = {NULL}, *data = &data_struct;
	char *prompt = " ";
	
	initialize_data(data, argc, argv, env);
	signal(SIGINT, hand_ctrl);
	
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prompt = PROMPT_MSG;
	}
	errno = 0;
	inf_loop(prompt, data);
	return (0);
}
/**
 * hand_ctrl - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void hand_ctrl(int opr unused)
{
	my_printf("\n");
	my_printf(PROMPT_MSG);
}

/**
 * initialize_data - inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void initialize_data(file_of_prog *data, int argc, char *argv[], char **env)
{
	int i = 0;
	data->prog_name = argv[0];
	data->inp_line = NULL;
	data->com_name = NULL;
	data->exec_count = 0;

	if (argc == 1)
		data->file_des = STDIN_FILENO;
	else
	{
		data->file_des = open(argv[1], O_RDONLY);
		if (data->file_des == -1)
		{
			my_printf_err(data->prog_name);
			my_printf_err(":0:Cant Access!");
			my_printf_err(argv[1]);
			my_printf_err("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 64);
	if (env)
	{
		for (; env[i]; i++)
		{
			data->env[i] = str_dup(env[i])
		}
	}
	data->env[i] = NULL;
	env = data->env;
	data->alias_lt = malloc(sizeof(char *) * 30);
	
	for (i = 0; i <30; i++)
	{
		data->alias_lt[i] = NULL;
	}
}

/**
 * inf_loop - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void inf_loop(char *prompt, file_of_prog *data)
{
	int err_cd = 0;
	int str_len = 0;

	while (++(data->exec_count))
	{
		my_printf(prompt);
		err_cd = str_len = my_getline(data);
		if (err_cd == EOF)
		{
			free_all_data(data);
			exit(errno);
		}
		if (str_len >= 1)
		{
			exp_alias(data);
			exp_var(data);
			token(data);
			if (data->tokens[0])
			{
				err_cd = excecmd(data);
				if (err_cd != 0)
					my_printf_error(err_cd, data);
			}
			free_recur_data(data);
		}
	}
}
