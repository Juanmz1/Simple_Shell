#include "shell.h"

/**
 * my_strtok - separate strings with delimiters
 * @line: - recieve in getline
 * @deli: - that separate the string with variable
 * Return: A pointer to the created token
 */
char *my_strtok(char *line, char *deli)
{
	int j;
	static char *str;
	char *str_cpy;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for(j = 0; deli[j] != '\0'; j++)
		{
			if (*str == deli[j])
				break;
		}
		if (deli[j] == '\0')
			break;
	}
	str_cpy = str;
	if (*str_cpy == '\0')
		return (NULL);
	for (; str != '\0'; str++)
	{
		for(j = 0; deli[j] != '\0'; j++)
		{
			if (*str == deli[j])
			{
				*str = '\0';
				str++;
				return (str_cpy);
			}
		}
	}
	return (str_cpy);
}
