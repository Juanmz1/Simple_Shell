/**
* my_getline - read one line from the prompt.
* @data: struct for the program's data
*
* Return: reading counting bytes.
*/
int my_getline(file_of_prog *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *array_cmd[10] = {NULL};
	static char array_op[10] = {'\0'};
	ssize_t bytes_read, i = 0;

	if (!array_cmd[0] || (array_op[0] == '&' && errno != 0) || (array_op[0] == '|' && errno == 0))
	{
		for (i = 0; array_cmd[i]; i++)
		{
			free(array_cmd[i]);
			array_cmd[i] = NULL;
		}
		bytes_read = read(data->file_des, &buff, BUFFER_SIZE -1)
			if (bytes_read == 0)
				return (-1);
		i = 0;
		do
		{
			array_cmd[i] = str_dup(my_strtok( i ? NULL : buff, "\n");
			i = chk_log_op(array_cmd, i, array_op);
		}
			while(array_cmd[i++];
	}
	data->inp_line = array_cmd[0];
	for (i = 0; array_cmd[i]; i++)
	{
		array_cmd[i] = array_cmd[i + 1];
		array_op[i] = array_op[i + 1];
	}
	return (str_len(data->inp_line);
}
/**
* chk_log_op - checks and split for && and || operators
* @array_cmd: array of the commands.
* @i: index in the array_commands to be checked
* @array_op: array of the logical operators for each previous command
*
* Return: index of the last command in the array_commands.
*/
int chk_log_op(char *array_cmd, int i, char array_op)
{
	char *temp = NULL;
	int j;

	for (j = 0; array_cmd[i] != NULL && array_cmd[i][j]; j++)
	{
		if (array_cmd[i][j] == '|' && array_cmd[i][j + 1] == '|')
		{
			temp = array_cmd[i];
			array_cmd[i][j] = '\0';
			array_cmd[i] = str_dup(array_cmd[i]);
			array_cmd[i + 1] str_dup(temp + j + 2);
			i++;
			array_op[i] = '&';
			free(temp);
			j = 0;
		}
		if (array_cmd[i][j] == '|' && array_cmd[i][j + 1] == '|')
        	{
                	temp = array_cmd[i];
                	array_cmd[i][j] = '\0';
                	array_cmd[i] = str_dup(array_cmd[i]);
                	array_cmd[i + 1] str_dup(temp + j + 2);
                	i++;
                	array_op[i] = '|';
                	free(temp);
                	j = 0;
        	}
	}
	return (i);
}
