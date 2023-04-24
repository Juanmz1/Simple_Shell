#include "shell.h"

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 100

int main(int ac, char *argv[])
{
char input[MAX_COMMAND_LENGTH];
char *args[MAX_ARGUMENTS];
int status, i, j, background = 0;
while (1)
{
printf("$ ");
fgets(input, MAX_COMMAND_LENGTH, stdin);
if (input[strlen(input) - 1] == '\n')
{
input[strlen(input) - 1] = '\0';
}
args[0] = strtok(input, " ");
for (i = 1; i < MAX_ARGUMENTS; i++)
{
args[i] = strtok(NULL, " ");
if (args[i] == NULL)
{
break;
}
}
if (args[0] == NULL)
{
continue;
}
if (strcmp(args[0], "exit") == 0)
{
exit(0);
}
if (strcmp(args[i - 1], "&") == 0)
{
background = 1;
args[ i - 1] = NULL;
}
else
{
background = 0;
}
int num_cmds = 1, command_status = 0, operator = 0;
char **commands[MAX_ARGUMENTS];
commands[0] = args;
for (j = 0; j < i - 1; j++)
{
if (strcmp(args[j], "&&") == 0)
{
operator = 1;
args[j] = NULL;
}
else if (strcmp(args[j], "||") == 0)
{
operator = 2;
args[j] = NULL;
}
else
{
continue;
}
commands[num_cmds] = &args[j + 1];
num_cmds++;
if (operator == 1 && command_status != 0)
{
break;
}
else if (operator == 2 && command_status == 0)
{
break;
}
operator = 0;
}
for (j = 0; j < num_cmds; j++)
{
pid_t pid = fork();
if (pid == -1)
{
perror("fork error");
}
else if (pid == 0)
{
if (execvp(commands[j][0], commands[j]) == -1)
{
perror("execvp error");
exit(EXIT_FAILURE);
}
}
else
{
if (!background)
{
waitpid(pid, &status, 0);
command_status = WEXITSTATUS(status);
}
}
}
}
return (0);
}
