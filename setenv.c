#include "shell.h"

/**
 * main - point of entry
 * setenv - Initialize a new environment variable, or modify an existing one
 * unsetenv - Remove an environment variable
 * Returns: 0
 */

int main ()
{
char* args [MAX_ARGS];
char arg_buffer[MAX_ARG_LENGTH];
int num_args = 0;

while (1)
{
printf("> ");
fflush(stdout);

/**
read the input line 
*/
      
char input_buffer[MAX_ARG_LENGTH];
fgets(input_buffer, MAX_ARG_LENGTH, stdin);

 /**
tokenize input line into argument
 */
num_args = 0;
char* arg = strtok (input_buffer, "\n");
while (arg != NULL && num_args < MAX_ARGS)
args[num_args++] = arg;
arg = strtok(NULL, "\n");
}
args[num_args] = NULL;
if (num_args == 0)
{
/**
Empty command, ignore
*/
continue;
}
if (strcmp(args[0], "setenc") == 0)
{
/**
setenv command
*/
if (num_args != 3)
{
fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
}
}
}
else if (strcmp(args[0], "unsetenv") == 0)
{
/**
unsetenv command
*/
if (num_args != 2)
{
fprintf(stderr, "Usage: unsetenv VARIABLE\n");
}
else
{
if (unsetenv(args[1]) != 0)
{
fprintf(stderr, "Failed to unset enviroment variable\n");
}
}
}
else
{
/**
Unsupported command, ignore
*/
continue;
}
return (0);
}
