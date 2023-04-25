#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMANDS 10
#define MAX_ARGS 10
#define MAX_BUFFER_SIZE 102

int main(int argc, char *argv[])
{
char buffer[MAX_BUFFER_SIZE];
char* commands[MAX_COMMANDS][MAX_ARGS];
int num_commands = 0;
int i, j;

while (1)
{
printf("ishell@~$ ");
fflush(stdout);

/**
 *read input line
 */
if (fgets(buffer, MAX_BUFFER_SIZE, stdin) == NULL)
{
break;
}

/**
 *tokenize input line into commands
 */
char* command = strtok(buffer, ";\n");
num_commands = 0;
while (command != NULL && num_commands < MAX_COMMANDS)
{
/**
 *tokenize command into arguments
*/
char* arg = strtok(command, " ");
j = 0;
while (arg != NULL && j < MAX_ARGS - 1)
{
commands[num_commands][j++] = arg;
arg = strtok(NULL, " ");
}
commands[num_commands][j] = NULL;
num_commands++;
command = strtok(NULL, ";\n");
}

/**
 *execute commands
 */
for (i = 0; i < num_commands; i++)
{
if (commands[i][0] != NULL)
{
int pid = fork();
if (pid == -1)
{
perror("fork");
}
else if (pid == 0)
{
/**
*child process
*/
  
if (execvp(commands[i][0], commands[i]) == -1)
{
perror("execvp");
exit(EXIT_FAILURE);
}
}
else
{
/**
 *parent process
*/
int status;
if (wait(&status) == -1)
{
perror("wait");
}
else
{
printf("\n");
}
}
}
}
}

printf("\n");
return (0);
}
