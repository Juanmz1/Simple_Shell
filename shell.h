#ifndef SHELL_H
#define SHELL_H
#ifndef I_PRINTF_H
#define I_PRINTF_H

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
char *togetenv(char *cmd);
char *print_env(char *cmd);
size_t my_getline(char **lineptr, size_t *n, FILE *stream);
int i_printf(const char *format, ...);
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	int readfd;
	int histcount;
	int cmd_buf_type;
} info_t;

ssize_t get_input(info_t *);
int my_getline(info_t *, char **, size_t *);
void sigHand(int);

#endif
