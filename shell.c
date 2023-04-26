#include "shell.h"

#define MAX_ARGS 10
#define MAX_LINE_LENGTH 10000

void execute(char *command)
{
char *args[MAX_ARGS];
int argc = 0;
char *token = strtok(command, " \n\t");

while (token != NULL && argc < MAX_ARGS - 1)
{
args[argc++] = token;
token = strtok(NULL, " \n\t");
}
args[argc] = NULL;

if (argc == 0)
{
return;
}

if (strcmp(args[0], "exit") == 0)
{
exit(0);
}

pid_t pid = fork();

if (pid == -1)
{
perror("fork");
return;
}

if (pid == 0)
{
int result = execvp(args[0], args);
if (result == -1)
{
perror(args[0]);
exit(1);
}
}
else
{
waitpid(pid, NULL, 0);
}
}

int main(int argc, char **argv)
{
char line[MAX_LINE_LENGTH];
FILE *fp = stdin;

if (argc == 2)
{
fp = fopen(argv[1], "r");
if (fp == NULL)
{
perror(argv[1]);
return (1);
}
}

while (fgets(line, MAX_LINE_LENGTH, fp))
{
if (line[0] == '#' || line[0] == '\n')
{
continue;
}

execute(line);
}

if (argc == 2)
{
fclose(fp);
}

return (0);
}