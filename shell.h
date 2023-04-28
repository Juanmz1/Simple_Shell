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
#include <stddef.h>
#include <fcntl.h>
#include <errno.h>

#include "macros.h"
/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliase
 */
typedef struct info
{
	char *prog_name;
	char *inp_line;
	char *com_name;
	int exec_count;
	int file_des;
	char **tokens;
	char **env;
	char **alias_lt;
} file_of_prog;
/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(file_of_prog *data);
} builtin_t;
/*main.c*/
void initialize_data(file_of_prog *data);
void inf_loop(char *prompt, file_of_prog *data);
void hand_ctrl(int opr unused);
/*getline*/
int my_getline(file_of_prog *data);
int chk_log_op(char *array_cmd[], int i, char array_op[]);
/*expan*/
void exp_var(file_of_prog *data);
void exp_alias(file_of_prog *data);
int buff_add(char *buff, char *str);
void token(file_of_prog *data);
char *my_strtok(char *line, char *deli);
int excecmd(file_of_prog *data);
int builtin_lt(file_of_prog *data);
/*
void exit_shell(int status);
char **token_cmd(char *lineptr_cpy);
extern char **environ;
void excecmd(char **arr);
int main(int ac, char *argv[]);
char *togetenv(char *cmd);
char *print_env(char *cmd);*/

#endif
