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
	if (_strcmp(array[0], "setenv") == 0)
	{
		_setenv_builtin(array, argv);
		return (0);
	}
	if (_strcmp(array[0], "unsetenv") == 0)
	{
		_unsetenv_builtin(array, argv);
		return (0);
	}
	if (_strcmp(array[0], "cd") == 0)
	{
		_cd_builtin(array, argv);
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

/**
 * _setenv_builtin - sets an environment variable
 * @cmd_args: command arguments
 * @main_argv: main arguments
 * Return: 0
 */

int _setenv_builtin(char **cmd_args, char **main_argv)
{
	int arg_count = 0, ret_val = 0;
	char *var_name = NULL;
	char *var_value = NULL;
	(void)main_argv;

	while (cmd_args[arg_count] != NULL)
		arg_count++;

	if (arg_count != 3)
	{
		write(STDERR_FILENO, "setenv: requires 2 arguments\n", 29);
		return (1);
	}

	var_name = malloc(_strlen(cmd_args[1]) + 1);
	if (var_name == NULL)
		return (1);

	var_value = malloc(_strlen(cmd_args[2]) + 1);
	if (var_value == NULL)
		return (1);

	_strcpy(var_name, cmd_args[1]);
	_strcpy(var_value, cmd_args[2]);

	ret_val = setenv(var_name, var_value, 1);
	free(var_name);
	free(var_value);
	if (ret_val != 0)
	{
		write(STDERR_FILENO, "setenv: failed to set variable\n", 31);
		return (1);
	}
	return (0);
}

/**
 * _unsetenv_builtin - unsets an environment variable
 * @cmd_args: command arguments
 * @main_argv: main arguments
 * Return: 0
 */
int _unsetenv_builtin(char **cmd_args, char **main_argv)
{
	int arg_count = 0, ret_val = 0;
	char *var_name = NULL;
	(void)main_argv;

	while (cmd_args[arg_count] != NULL)
		arg_count++;

	if (arg_count != 2)
	{
		write(STDERR_FILENO, "unsetenv: requires 1 argument\n", 30);
		return (1);
	}

	var_name = malloc(_strlen(cmd_args[1]) + 1);
	if (var_name == NULL)
		return (1);

	_strcpy(var_name, cmd_args[1]);

	ret_val = unsetenv(var_name);
	free(var_name);
	if (ret_val != 0)
	{
		write(STDERR_FILENO, "unsetenv: failed to unset variable\n", 36);
		return (1);
	}
	return (0);
}
