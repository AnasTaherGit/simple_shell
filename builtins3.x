#include "shell.h"

/**
 * _cd_builtin - changes the current working directory
 * @cmd_args: command arguments
 * @main_argv: main arguments
 * Return: 0
 */

int _cd_builtin(char **cmd_args, char **main_argv)
{
    char *home = NULL, *oldpwd = NULL, *pwd = NULL, *cwd = NULL;
    int status = 0;

    if (cmd_args[1] == NULL)
    {
        home = _getenv("HOME");
        if (home == NULL)
        {
            write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
            write(STDERR_FILENO, ": 1: cd: HOME not set\n", 22);
            return (1);
        }
        status = chdir(home);
        if (status == -1)
        {
            write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
            write(STDERR_FILENO, ": 1: cd: can't cd to HOME\n", 26);
            return (1);
        }
    }
    else if (_strcmp(cmd_args[1], "-") == 0)
    {
        oldpwd = _getenv("OLDPWD");
        if (oldpwd == NULL)
        {
            write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
            write(STDERR_FILENO, ": 1: cd: OLDPWD not set\n", 24);
            return (1);
        }
        status = chdir(oldpwd);
        if (status == -1)
        {
            write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
            write(STDERR_FILENO, ": 1: cd: can't cd to OLDPWD\n", 28);
            return (1);
        }
    }
    else
    {
        status = chdir(cmd_args[1]);
        if (status == -1)
        {
            write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
            write(STDERR_FILENO, ": 1: cd: can't cd to ", 21);
            write(STDERR_FILENO, cmd_args[1], _strlen(cmd_args[1]));
            write(STDERR_FILENO, "\n", 1);
            return (1);
        }
    }
    pwd = _getenv("PWD");
    if (pwd == NULL)
    {
        write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
        write(STDERR_FILENO, ": 1: cd: PWD not set\n", 21);
        return (1);
    }
    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
        write(STDERR_FILENO, ": 1: cd: can't get current working directory\n", 45);
        return (1);
    }
    status = setenv("OLDPWD", pwd, 1);
    if (status == -1)
    {
        write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
        write(STDERR_FILENO, ": 1: cd: can't set OLDPWD\n", 26);
        return (1);
    }
    status = setenv("PWD", cwd, 1);
    if (status == -1)
    {
        write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
        write(STDERR_FILENO, ": 1: cd: can't set PWD\n", 23);
        return (1);
    }
    free(cwd);
    return (0);
}