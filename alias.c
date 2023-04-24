#include "shell.h"
#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 100
#define MAX_ALIASES 100

int main(int ac, char *av[]);
void parse_input(char *input, char **args);
void execute_command(char **args, int *status);
void handle_logical_operators(char **args, int *status);
void print_aliases(void);
void set_alias(char *name, char *value);
char *get_alias_value(char *name);
void unset_alias(char *name);

char input[MAX_COMMAND_LENGTH];
char *args[MAX_ARGUMENTS];
int status = 0;
char *aliases[MAX_ALIASES][2];
int num_aliases = 0;

int main(int ac, char *av[])
{
while (1)
{
printf("$ ");
fgets(input, MAX_COMMAND_LENGTH, stdin);

if (input[strlen(input) - 1] == '\n')
{
input[strlen(input) - 1] = '\0';
}

parse_input(input, args);
handle_logical_operators(args, &status);
execute_command(args, &status);
}

return (0);
}

void parse_input(char *input, char **args)
{
args[0] = strtok(input, " ");
int i = 1;
while (args[i - 1] != NULL && i < MAX_ARGUMENTS - 1)
{
args[i] = strtok(NULL, " ");
i++;
}
}

void execute_command(char **args, int *status)
{
pid_t pid = fork();

if (pid == -1)
{
perror("fork error");
}
else if (pid == 0)
{
char *command = args[0];
char *value = get_alias_value(command);
if (value != NULL)
{
args[0] = value;
}

execvp(args[0], args);
perror("execvp error");
exit(EXIT_FAILURE);
}
else
{
    waitpid(pid, status, 0);
}


void handle_logical_operators(char **args, int *status)
{
int i = 0;
while (args[i] != NULL)
{
if (strcmp(args[i], "&&") == 0)
{
if (*status != 0)
{
args[i] = NULL;
}
else
{
int j = i;
while (args[j] != NULL)
{
args[j] = args[j + 2];
j++;
}
i--;
}
}
else if (strcmp(args[i], "||") == 0)
{
if (*status == 0)
{
args[i] = NULL;
}
else
{
int j = i;
while (args[j] != NULL)
{
args[j] = args[j + 2];
j++;
}
i--;
}
}
i++;
}
}

void print_aliases(void)
{
for (int i = 0; i < num_aliases; i++)
{
printf("%s='%s'\n", aliases[i][0], aliases[i][1]);
}
}

void set_alias(char *name, char *value)
{
for (int i = 0; i < num_aliases; i++)
{
if (strcmp(aliases[i][0], name) == 0)
{
strcpy(aliases[i][1], value);
return;
}
}
if (num_aliases < MAX_ALIASES)
{
aliases[num_aliases][0] = strdup(name);
aliases[num_aliases][1] = strdup(value);
num_aliases++;
}
else
{
printf("Too many aliases defined\n");
}
