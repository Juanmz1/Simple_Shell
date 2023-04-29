#include "shell.h"
/**
 * exp_var - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void exp_var(file_of_prog *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expan[BUFFER_SIZE] = {'\0'};
	char *temp;

	if(data->inp_line == NULL)
		return;
	buff_add(line, data->inp_line);
	for (i = 0; line[i]; i++)
		if(line[i] == '#')
			line[i--] == '\0';
		else if (line[i] == '$' && line[i +1] == '?')
		{
			line[i] = '\0';
			long_str(errno, expan, 10);
			buff_add(line, expan);
			buff_add(line, data->inp_line + i + 2);
		}
		else if (line[i] == '$' && line[i +1] == '$')
                {       
                        line[i] = '\0';
                        long_str(getpid(), expan, 10);
                        buff_add(line, expan);
                        buff_add(line, data->inp_line + i + 2);
                }
		else if (line[i] == '$' && line[i +1] == ' ' || line[i + 1] == '\0')
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expan[j - 1] = line[i + j];
			temp = env_get(expan, data);
			line[i] = '\0', expan[0] = '\0';
			buff_add(expan, line + i + j);
			temp ? buff_add(line, expan) : 1;
			buff_add(line, expan);
		}
	if (!str_cmp(data->inp_line, line, 0))
	{
		free(data->inp_line);
		data->inp_line = str_dup(line);
	}
}


/**
 * exp_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void exp_alias(file_of_prog *data)
{
	int i, j, w_exp = 0;
	char line[BUFFER_SIZE] = {0}, expan[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->inp_line == NULL)
		return;

	buff_add(line, data->inp_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expan[j] = line[i + j];
		expan[j] = '\0';

		temp = get_alias(data, expan);
		if (temp)
		{
			expan[0] = '\0';
			buff_add(expan, line + i + j);
			line[i] = '\0';
			buff_add(line, temp);
			line[str_len(line)] = '\0';
			buff_add(line, expan);
			w_exp = 1;
		}
		break;
	}
	if (w_exp)
	{
		free(data->inp_line);
		data->inp_line = str_dup(line);
	}
}

/**
 * buff_add - append string at end of the buffer
 * @buff: buffer to be filled
 * @str: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buff_add(char *buff, char *str)
{
	int len, i;

	len = str_len(buff);
	for (i = 0; str[i]; i++)
	{
		buff[len + i] = str[i];
	}
	buff[len + i] = '\0';
	return (len + i);
}
