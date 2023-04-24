#include "shell.h"

#define MAX_ARGS 10
#define MAX_ARGUMENTS 100

/**
 * main - point of entry
 * setenv - Initialize a new environment variable, or modify an existing one
 * unsetenv - Remove an environment variable
 * Returns: 0
 */

int main(int ac, char *argv[])
{
    char *args[MAX_ARGS];
    char arg_buffer[MAX_ARGUMENTS];
    int num_args = 0;

    while (1)
    {
        printf("> ");
        fflush(stdout);

        /**
         * read the input line 
        */

        char input_buffer[MAX_ARGUMENTS];
        fgets(input_buffer, MAX_ARGUMENTS, stdin);

        /**
         * tokenize input line into argument
        */
        num_args = 0;
        char *arg = strtok(input_buffer, " ");
        while (arg != NULL && num_args < MAX_ARGS)
        {
            args[num_args++] = arg;
            arg = strtok(NULL, " ");
        }

        args[num_args] = NULL;
        if (num_args == 0)
        {
            /**
             * Empty command, ignore
            */
            continue;
        }
        else if (strcmp(args[0], "setenv") == 0)
        {
            /**
            setenv command
            */
            if (num_args != 3)
            {
                fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
            }
            else
            {
                if (setenv(args[1], args[2], 1) != 0)
                {
                    perror("Failed to set environment variable");
                }
            }
        }
        else if (strcmp(args[0], "unsetenv") == 0)
        {
            /**
             * unsetenv command 
            */
            if (num_args != 2)
            {
                fprintf(stderr, "Usage: unsetenv VARIABLE\n");
            }
            else
            {
                if (unsetenv(args[1]) != 0)
                {
                    perror("Failed to unset environment variable");
                }
            }
        }
        else
        {
            /**
            Unsupported command, ignore
            */
        }
    }
    return (0);
}
