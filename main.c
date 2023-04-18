#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @argv: arg vector
 * Return: 0 
*/

int main (int ac, char **argv)
{
  char *prompt = "(Ishell) $ ";
  char *lineptr;
  size_t n = 0;
  ssize_t n_char;

  while (1)
  {
	  printf ("%s", prompt);
	  n_char = getline(&lineptr, &n, stdin);
	  printf("%s\n", lineptr);
	  if (n_char == -1)
	  {
		  perror("command not found -> End of File/use of Ctrl+D");
		  return (-1);
	  }
  }
	  free (lineptr);
	  return (0);
}
