#include "shell.h"

/**
 * cd_change_directory - Changes the current working directory
 * @path: Path to change directory to
 * @command_name: Name of the command (for error messages)
 * Return: 0 on success, 1 on failure
 */
int cd_change_directory(const char *path, const char *command_name)
{
	if (chdir(path) == -1)
	{
		write(STDERR_FILENO, command_name, _strlen(command_name));
		write(STDERR_FILENO, ": 1: cd: can't cd to ", 21);
		write(STDERR_FILENO, path, _strlen(path));
		return (1);
	}

	return (0);
}

/**
 * cd_update_environment - Updates the PWD and OLDPWD environment variables
 * @command_name: Name of the command (for error messages)
 * Return: 0 on success, 1 on failure
 */
int cd_update_environment(const char *command_name)
{
	char *cwd = getcwd(NULL, 0);
	char *pwd = _getenv("PWD");

	if (!cwd)
	{
		write(STDERR_FILENO, command_name, _strlen(command_name));
		write(STDERR_FILENO, ": 1: cd: can't get current working directory\n", 45);
		return (1);
	}

	if (setenv("OLDPWD", pwd ? pwd : "", 1) == -1)
	{
		write(STDERR_FILENO, command_name, _strlen(command_name));
		write(STDERR_FILENO, ": 1: cd: can't set OLDPWD\n", 26);
		return (1);
	}

	if (setenv("PWD", cwd, 1) == -1)
	{
		dprintf(STDERR_FILENO, "%s: 1: cd: can't set PWD\n", command_name);
		return (1);
	}

	free(cwd);
	return (0);
}

/**
 * _cd_builtin - Changes the current working directory
 * @cmd_Args: Command arguments
 * @main_argv: Main arguments
 * Return: 0 on success, 1 on failure
 */
int _cd_builtin(char **cmd_Args, char **main_argv)
{
	char *new_dir, *cwd = NULL;
	int display_path = 0;

	cwd = getcwd(NULL, 0);

	if (cmd_Args[1] == NULL || _strcmp(cmd_Args[1], "~") == 0)
		new_dir = _getenv("HOME");
	else if (_strcmp(cmd_Args[1], "-") == 0)
	{
		new_dir = _getenv("OLDPWD");
		display_path = 1;
	}
	else
	{
		new_dir = malloc((_strlen(cmd_Args[1]) + 1) * sizeof(char));
		_strcpy(new_dir, cmd_Args[1]);
	}

	if (new_dir == NULL)
	{
		free(new_dir);
		new_dir = getcwd(NULL, 0);
	}
	else if (chdir(new_dir) != 0)
	{
		write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
		write(STDERR_FILENO, ": 1: cd: can't cd to ", 21);
		write(STDERR_FILENO, new_dir, _strlen(new_dir));
		write(STDERR_FILENO, "\n", 1);
		free(new_dir);
		return (1);
	}
	setenv("PWD", new_dir, 1);
	setenv("OLDPWD", cwd, 1);
	if (display_path)
	{
		write(STDOUT_FILENO, new_dir, _strlen(new_dir));
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}
