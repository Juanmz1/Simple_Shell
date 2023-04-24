#include "shell.h"


#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 100

int main(int ac, char *argv[]);
char input[MAX_COMMAND_LENGTH];
char *args[MAX_ARGUMENTS];
int status, i;
{
while (1)
{
printf("$ ");
fgets(input, MAX_COMMAND_LENGTH, stdin);

if (input[strlen(input) - 1] == '\n')
{
input[strlen(input) - 1] = '\0';
}
args[0] = input;

for (i = 1; i < MAX_ARGUMENTS; i++)
{
args[i] = NULL;
}

for (i = 0; i < MAX_COMMAND_LENGTH; i++)
{
if (input[i] == ' ')
{
input[i] = '\0';
args[1] = &input[i + 1];
break;
}
}

pid_t pid = fork();

if (pid == -1)
{
perror("fork error");
}
else if (pid == 0)
{
execvp(args[0], args);
perror("execvp error");
exit(EXIT_FAILURE);
}
else
{
waitpid(pid, &status, 0);
}

return (0);
}
