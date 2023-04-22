#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MAX_INPUT_LENGTH 1024
#define MAX_COMMANDS 10
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#define MAX_ARGS 10
#define MAX_ARGUMENTS 100
void exit_shell(int status);
char **token_cmd(char *lineptr_cpy);
extern char **environ;
void excecmd(char **arr);
int main(int ac, char *argv[]);
char *fcheck(char *cmd);
int pcheck(char *cmd);
char *togetenv(char *cmd);
char *print_env(char *cmd);

#endif
