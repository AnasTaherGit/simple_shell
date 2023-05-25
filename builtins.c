#include "shell.h"

/**
 * check_builtins - checks for builtins
 * @array: array of commands and arguments
 * @line: user input
 * Return: 0
 */
int check_builtins(char **array)
{
	if (_strcmp(array[0], "exit") == 0)
	{
		_exit_builtin(array);
		return (0);
	}
	return (1);
}

/**
 * _exit_builtin - exits the shell
 * @cmd_args: command arguments
 * @line: user input
 * Return: 0
 */
int _exit_builtin(char **cmd_args)
{
	int status = 0;
	/*
	if (cmd_args[1] == NULL)
	{

	}
	else
	{
		status = _atoi(cmd_args[1]);
		free_null_terminated_array(cmd_args);
		exit(status);
	}*/
	free_null_terminated_array(cmd_args);
	exit(status);
	return (0);
}
