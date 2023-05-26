#include "shell.h"

/**
 * _cd_builtin - Changes the current working directory
 * @cmd_Args: Command arguments
 * @main_argv: Main arguments
 * Return: 0 on success, 1 on failure
 */
int _cd_builtin(char **cmd_Args, char **main_argv)
{
	char *new_dir = NULL, *home_dir = NULL, *old_dir = NULL, *arg_dir = NULL;
	char *cwd = NULL;
	int display_path = 0;

	cwd = getcwd(NULL, 0);

	if (cmd_Args[1] == NULL || _strcmp(cmd_Args[1], "~") == 0)
		home_dir = _getenv("HOME");
	else if (_strcmp(cmd_Args[1], "-") == 0)
	{
		old_dir = _getenv("OLDPWD");
		display_path = 1;
	}
	else
		arg_dir = get_new_directory(cmd_Args);

	new_dir = select_directory(home_dir, old_dir, arg_dir, cwd);
	free(arg_dir);

	if (chdir(new_dir) != 0)
	{
		write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
		write(STDERR_FILENO, ": 1: cd: can't cd to ", 21);
		write(STDERR_FILENO, new_dir, _strlen(new_dir));
		write(STDERR_FILENO, "\n", 1);
		free(new_dir);
		free(cwd);
		return (1);
	}
	set_environment_variables(new_dir, cwd);
	if (display_path)
	{
		write(STDOUT_FILENO, new_dir, _strlen(new_dir));
		write(STDOUT_FILENO, "\n", 1);
	}
	free(cwd);
	free(new_dir);
	return (0);
}
/**
 * get_new_directory - gets the new directory
 * @cmd_Args: Command arguments
 * Return: new directory
 */
char *get_new_directory(char **cmd_Args)
{
	char *new_dir = NULL;

	new_dir = malloc((_strlen(cmd_Args[1]) + 1) * sizeof(char));
	_strcpy(new_dir, cmd_Args[1]);
	return (new_dir);
}

/**
 * set_environment_variables - sets the environment variables
 * @new_dir: new directory
 * @cwd: current working directory
 * Return: void
 */
void set_environment_variables(char *new_dir, char *cwd)
{
	setenv("OLDPWD", cwd, 1);
	setenv("PWD", new_dir, 1);
}

/**
 * select_directory - selects the directory
 * @home_dir: home directory
 * @old_dir: old directory
 * @arg_dir: argument directory
 * @cwd: current working directory
 * Return: new directory
 */
char *select_directory(char *home_dir, char *old_dir, char *arg_dir, char *cwd)
{
	char *new_dir = NULL;

	if (home_dir != NULL)
	{
		new_dir = malloc((_strlen(home_dir) + 1) * sizeof(char));
		_strcpy(new_dir, home_dir);
	}
	else if (old_dir != NULL)
	{
		new_dir = malloc((_strlen(old_dir) + 1) * sizeof(char));
		_strcpy(new_dir, old_dir);
	}
	else if (arg_dir != NULL)
	{
		new_dir = malloc((_strlen(arg_dir) + 1) * sizeof(char));
		_strcpy(new_dir, arg_dir);
	}
	else
	{
		new_dir = malloc((_strlen(cwd) + 1) * sizeof(char));
		_strcpy(new_dir, cwd);
	}
	return (new_dir);
}
