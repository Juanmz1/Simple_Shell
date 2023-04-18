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
  
  printf ("%s", prompt);
getline(&lineptr, &n, stdin);
 printf("%s\n", lineptr);
 
  free (lineptr);
  return (0);
}
