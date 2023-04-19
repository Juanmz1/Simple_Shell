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
#define MAX_ARGUMENTS 10

int token_cmd(char *command, char *const argv[]);
extern char **environ;
<<<<<<< HEAD
void excecmd(char *const argv[], char *const envp[]);
int main(int ac, char *const argv[], char *const envp[]);
=======
<<<<<<< HEAD
char *get_location(char *command);
void excecmd(char **argv, char **envp);
int main(int ac, char **argv, char **envp);
>>>>>>> c9ae6cca92e808eacef019660c45fee1e567e6b3
>>>>>>> 76d01e0b034520c6fd21700581195c4b8b32582e

#endif
