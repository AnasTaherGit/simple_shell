#include "shell.h"

/**
 * check_builtins - checks for builtins
 * @array: array of commands and arguments
 * @last_exit_status: last exit status
 * @argv: main arguments
 * Return: 0
 */
int check_builtins(char **array, char **argv, int last_exit_status)
{
	if (_strcmp(array[0], "exit") == 0)
	{
		_exit_builtin(array, argv, last_exit_status);
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
 * @last_exit_status: last exit status
 * @main_argv: main arguments
 * Return: 0
 */
int _exit_builtin(char **cmd_args, char **main_argv, int last_exit_status)
{
	int status = EXIT_SUCCESS;

	if (cmd_args[1] == NULL)
	{
		free_null_terminated_array(cmd_args);
		if (last_exit_status != 0)
			exit(2);
		else
			exit(status);
	}
	else
	{
		status = is_valid_number(cmd_args[1]);
		if (status < 0)
		{
			write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
			write(STDERR_FILENO, ": 1: exit: Illegal number: ", 27);
			write(STDERR_FILENO, cmd_args[1], _strlen(cmd_args[1]));
			write(STDERR_FILENO, "\n", 1);
			free_null_terminated_array(cmd_args);
			exit(2);
		}
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
