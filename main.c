#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @argv: arg vector
 * Return: 0 
*/

int main (int ac, char **argv)
{
<<<<<<< HEAD
	char *prompt = "(Ishell) $ ";
	char *lineptr = NULL, *lineptr_cpy = NULL;
	const char *deli = " \n";
	size_t n = 0;
	ssize_t n_char;
	char *token;
	int i;
	int token_count;
	(void)ac;
	
	while (1)
	{
		printf ("%s", prompt);
		n_char = getline(&lineptr, &n, stdin);
		if (n_char == -1)
		{
			printf("command not found -> End of File/use of Ctrl+D");
			return (-1);
		}
		//memory allocation of the lineptr_cpy//
		lineptr_cpy = malloc(sizeof(char) *n_char);
		if (lineptr_cpy == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}
		// copy the lineptr to the lineptr_cpy//
		strcpy(lineptr_cpy, lineptr);
		// calculate the number of token//
		token = strtok(lineptr, deli);
		while (token != NULL)
		{
			token_count++;
			token = strtok(NULL, deli);
		}
		token_count++;
		// allocate a space to hold the array of string
		argv = malloc(sizeof(char *) *token_count);
		// store the token in the array
		token = strtok(lineptr_cpy, deli);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) *strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, deli);
		}
		argv[i] = NULL;
		exec(argv);
	}
		
		printf("%s\n", lineptr);
		for (i = 0; i < token_count - 1; i++)
		{
			printf("%s\n", argv[i]);
		}

		free(lineptr);
		free(lineptr_cpy);
	}
	return (0);
=======
  char *prompt = "(Ishell) $ ";
  char *lineptr;
  size_t n = 0;
  ssize_t n_char;
  

  while (1)
  {
	  printf ("%s", prompt);
	  n_char = getline(&lineptr, &n, stdin);
	 
	  if (n_char == -1)
	  
	    {
		  perror("command not found -> End of File/use of Ctrl+D");
		  return (-1);
	  }
	  printf("%s\n", lineptr);
  }
=======
	  if (n_char == -1)
	  {
		  printf("command not found -> End of File/use of Ctrl+D");
		  return (-1);
	  }
	  printf("%s\n", lineptr);
	  
>>>>>>> d4dd5ec73671d6c7f0b22f81ddc2cc51bf586fbc
	  free (lineptr);
  }
  return (0);
>>>>>>> 84fb9050a091a04b787e6829a9061dd98b32c610
}
