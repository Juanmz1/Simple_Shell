#include "shell.h"

#define MAX_ARGS 10

int main(int argc, char *argv[])
{
char *line = NULL;
size_t len = 0;
ssize_t read;
char *args[MAX_ARGS];
int i, status;
pid_t pid;

while (1)
{
printf("$ ");
if ((read = getline(&line, &len, stdin)) == -1)
{
break;
}

/**
 *Remove newline character
 */
line[strcspn(line, "\n")] = '\0';

/**
 *Skip comment lines
 */
if (line[0] == '#')
{
continue;
}

/**
 *Tokenize input line into arguments
 */
char *token = strtok(line, " ");
i = 0;
while (token != NULL)
{
args[i++] = token;
token = strtok(NULL, " ");
}
args[i] = NULL;

/**
 *Execute command
 */
if ((pid = fork()) == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
  /**
   *Child process
   */
execvp(args[0], args);
perror("execvp");
exit(EXIT_FAILURE);
}
else
{
  /**
   *Parent process
   */
wait(&status);
}
}

free(line);
exit(EXIT_SUCCESS);
}