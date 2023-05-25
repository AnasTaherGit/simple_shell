#include "shell.h"

/**
 * cmd_handle - handles command
 * @cmd_args: command arguments
 * @line: user input to clear if needed
 * @main_argv: main arguments
 * Return: 0
 */
int cmd_handle(char **cmd_args, char **main_argv)
{
	struct stat file_stat = {0};
	char *path = NULL;

	/*
	if (check_builtins(cmd_args) == 0)
	{
		return (0);
	}*/

	if (stat(cmd_args[0], &file_stat) == 0 && access(cmd_args[0], X_OK) == 0)
	{
		launch_process(cmd_args, main_argv[0]);
		return (0);
	}
	/*
	path = get_full_path(cmd_args[0]);

	if (path != NULL)
	{
		cmd_args[0] = malloc(sizeof(char) * (_strlen(path) + 1));
		_strcpy(cmd_args[0], path);
		free(path);
		launch_process(cmd_args, main_argv[0]);
		return (0);
	}*/
	else
	{
		free(path);
		errno = ENOENT;
		perror(main_argv[0]);
	}
	return (0);
}

/**
 * launch_process - execute command
 * @command: command
 * @name: name of program
 * Return: 1
 */
int launch_process(char **command, char *name)
{
	pid_t pid = 0;

	if (command[1] != NULL)
	{
		errno = ENOENT;
		perror(name);
		return (0);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(command[0], command, environ) == -1)
		{
			perror(name);
		}
		free_null_terminated_array(command);
		_exit(EXIT_SUCCESS);
	}
	else
	{
		wait(NULL);
	}
	return (1);
}
