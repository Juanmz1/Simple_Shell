#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#define MAX_INPUT_LENGTH 1024
#define MAX_COMMANDS 10
#define MAX_ARGUMENTS 10

int token_cmd(char *command, char **argv);
extern char **environ;
void excecmd(char **argv, char **envp);
int main(int ac, char **argv, char **envp);

#endif
