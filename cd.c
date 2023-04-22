#include "shell.h"

int cd(char **args)
{
char *new_dir = args[1];
char old_dir[1024];
/**
 * buffer to store previous directory
*/

/**
 * if no argument is given, change to home directory
*/
if (!new_dir)
{
new_dir = getenv("HOME");
}

/**
 * if argument is "-", change to previous directory
*/

if (strcmp(new_dir, "-") == 0)
{
new_dir = getenv("OLDPWD");
printf("%s\n", new_dir);
}

/**
 * save current directory for later use
*/
if (getcwd(old_dir, sizeof(old_dir)) == NULL)
{
perror(getcwd);
return (1);
}

if (chdir(new_dir) != 0)
{
perror("cd");
return (1);
}

/**
 * update the PWD environment variable
*/
if (setenv("PWD", new_dir, 1) != 0)
{
perror("setenv");
return (1);
}

/**
 * update the OLDPWD environment variable
*/
if (setenv("OLDPWD", old_dir, 1) != 0)
{
perror("setenv");
return (1);
}
return (0);
}
