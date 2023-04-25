#include "shell.h"
#include <errno.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 10

int execute(char *args[]);
char *replace_variable(char *command);

int main(int argc, char *argv[])
{
char input[MAX_INPUT];
char *args[MAX_ARGS];
int status;

while (1)
{
printf("$ ");

if (!fgets(input, MAX_INPUT, stdin))
{
if (feof(stdin))
{
exit(0);
}
perror("fgets");
exit(1);
}

if (strcmp(input, "exit\n") == 0)
{
exit(0);
}

char *command = replace_variable(input);

char *token = strtok(command, " \n");
int i = 0;
while (token != NULL)
{
args[i++] = token;
token = strtok(NULL, " \n");
}
args[i] = NULL;

status = execute(args);

free(command);

if (status == -1) {
perror("execute");
exit(1);
}
}
}

int execute(char *args[])
{
pid_t pid, wpid;
int status;

pid = fork();
if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("execvp");
exit(1);
}
exit(0);
}
else if (pid < 0)
{
perror("fork");
exit(1);
}
else
{
do
{
wpid = waitpid(pid, &status, WUNTRACED);
}
while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

return (status);
}

char *replace_variable(char *command)
{
static char result[MAX_INPUT];
char *result_ptr = result;
char *var_ptr;
char var_name[3];
int var_value;

while (*command != '\0')
{
if (*command == '$' && *(command+1) != '\0')
{
var_ptr = command+1;
var_name[0] = *var_ptr;
var_name[1] = *(var_ptr+1);
var_name[2] = '\0';

if (strcmp(var_name, "$$") == 0)
{
var_value = getpid();
sprintf(result_ptr, "%d", var_value);
result_ptr += strlen(result_ptr);
command += 2;
}
else if (strcmp(var_name, "$?") == 0)
{
var_value = errno;
sprintf(result_ptr, "%d", var_value);
result_ptr += strlen(result_ptr);
command += 2;
}
else
{
command++;
}
}
else
{
*result_ptr++ = *command++;
}
}
*result_ptr = '\0';

return (result);
}
