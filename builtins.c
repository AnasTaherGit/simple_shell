#include "shell.h"

/**
 * check_builtins - checks for builtins
 * @array: array of commands and arguments
 * Return: 0
 */
int check_builtins(char **array)
{
	if (_strcmp(array[0], "exit") == 0)
	{
		_exit_builtin(array);
		return (0);
	}
	if (_strcmp(array[0], "env") == 0)
	{
		_env_builtin();
		return (0);
	}
	return (1);
}

/**
 * _exit_builtin - exits the shell
 * @cmd_args: command arguments
 * Return: 0
 */
int _exit_builtin(char **cmd_args)
{
	int status = 0;

	if (cmd_args[1] == NULL)
	{
		free_null_terminated_array(cmd_args);
		exit(status);
	}
	else
	{
		status = _atoi(cmd_args[1]);
		free_null_terminated_array(cmd_args);
		exit(status);
	}

	return (0);
}

/**
 * _env_builtin - prints the environment
 * Return: 0
 */
int _env_builtin(void)
{
	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (0);
}
