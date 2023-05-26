#include "shell.h"
#define MAX_PATH_LENGTH 4096
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
	char *new_dir = NULL;
	char current_dir[MAX_PATH_LENGTH];

	getcwd(current_dir, sizeof(current_dir));
	if (cmd_Args[1] == NULL || _strcmp(cmd_Args[1], "~") == 0)
		new_dir = _getenv("HOME");
	else if (strcmp(cmd_Args[1], "-") == 0)
		new_dir = _getenv("OLDPWD");
	else
		_strcpy(new_dir, cmd_Args[1]);
	if (new_dir == NULL)
	{
		setenv("PWD", current_dir, 1);
		write(STDOUT_FILENO, current_dir, strlen(current_dir));
		write(STDOUT_FILENO, "\n", 1);
		free(new_dir);
		return (0);
	}
	if (chdir(new_dir) != 0)
	{
		write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
		write(STDERR_FILENO, ": 1: cd: can't cd to ", 21);
		write(STDERR_FILENO, cmd_Args[1], _strlen(cmd_Args[1]));
		write(STDERR_FILENO, "\n", 1);
		setenv("PWD", current_dir, 1);
		free(new_dir);
		return (1);
	}
	setenv("PWD", new_dir, 1);
	setenv("OLDPWD", current_dir, 1);
	write(STDOUT_FILENO, current_dir, strlen(current_dir));
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
