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
#include <signal.h>
#include <stddef.h>
#include <fcntl.h>
#include <errno.h>

/* Prompt to be printed */
#define PROMPT_MSG "$" /* Needed to work with signal */

/* Resume from the unused attibute */
#define UNUSED __attribute__((unused))

/* buffer size for each read call in _getline */
#define BUFFER_SIZE 1024

/************* FORMATTED STRING FOR HELP BUILT IN **************/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Change the shell working directory.\n\n"\
"	If no argument is given to cd the command will be interpreted\n"\
"	as cd $HOME.\n"\
"	if the argumenthelp is - (cd -), the command will be interpreted\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit of the simple-shell.\n\n"\
"	Exits the shell with a status of N.  If N is omitted, the exit status\n"\
"	is that of the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command will be print a complete list of enviroment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	initialize a new environment variable, or modify an existing one\n"\
"	When there are not correct numbers of arguments print error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one variable from the environment.\n\n"\
"	Wen there are not correct numbers of arguments print error message.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display information about builtin commands.\n\n"\
"	Displays brief summaries of builtin commands.  If BUILTIN_NAME is\n"\
"	specified, gives detailed help on all commands matching BUILTIN_NAME,\n"\
"	otherwise the list of help topics is printed BUILTIN_NAME list.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifiying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"
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
} builtins;

/*main.c*/
void initialize_data(file_of_prog *data, int argc, char *argv[], char **env);
void inf_loop(char *prompt, file_of_prog *data);
void hand_ctrl(int opr UNUSED);
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
/*findpath*/
int find_prog(file_of_prog *data);
int **token_path(file_of_prog *data);
int check_file(char *full_path);
/*help*/
void free_arr_pointers(char **directories);
void free_recur_data(file_of_prog *data);
void free_all_data(file_of_prog *data);
/*builtin.more*/
int builtin_exit(file_of_prog *data);

/* Change the current directory */
int builtin_cd(file_of_prog *data);

/* set the work directory */
int set_wk_dir(file_of_prog *data, char *new_dir);

/* show help information */
int builtin_help(file_of_prog *data);

/* set, unset and show alias */
int builtin_alias(file_of_prog *data);


/*======== builtins_env.c ========*/

/* Shows the environment where the shell runs */
int builtin_env(file_of_prog *data);

/* create or override a variable of environment */
int builtin_set_env(file_of_prog *data);

/* delete a variable of environment */
int builtin_unset_env(file_of_prog *data);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_get(char *name, file_of_prog *data);

/* Overwrite the value of the environment variable */
int env_set(char *key, char *value, file_of_prog *data);

/* Remove a key from the environment */
int env_rem(char *key, file_of_prog *data);

/* prints the current environ */
void print_env(file_of_prog *data);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int my_printf(char *string);

/* Prints a string in the standar error */
int my_printf_e(char *string);

/* Prints a string in the standar error */
int my_printf_error(int errorcode, file_of_prog *data);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int str_len(char *string);

/* Duplicates an string */
char *str_dup(char *string);

/* Compares two strings */
int str_cmp(char *string1, char *string2, int number);

/* Concatenates two strings */
char *str_cat(char *string1, char *string2);

/* Reverse a string */
void str_rev(char *string);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void long_str(long number, char *string, int base);

/* convert an string in to a number */
int my_atoi(char *s);

/* count the coincidences of character in string */
int count_char(char *string, char *character);


/*======== alias_management.c ========*/

/* print the list of alias */
int print_alias(file_of_prog *data, char *alias);

/* get the alias name */
char *get_alias(file_of_prog *data, char *alias);

/* set the alias name */
int set_alias(char *alias_string, file_of_prog *data);


#endif
