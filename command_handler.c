#include "shell.h"

/**
 * cmd_handle - handles command
 * @cmd_args: command arguments
 * @main_argv: main arguments
 * @last_exit_status: last exit status
 * Return: 0
 */
int cmd_handle(char **cmd_args, char **main_argv, int last_exit_status)
{
	struct stat file_stat = {0};
	char *path = NULL, *cmd = NULL;
	int ret_value = 0;

	if (check_builtins(cmd_args, main_argv, last_exit_status) == 0)
		ret_value = 0;
	else if (cmd_args[0][0] == '/' || cmd_args[0][0] == '.')
	{
		if (stat(cmd_args[0], &file_stat) == 0 && access(cmd_args[0], X_OK) == 0)
			ret_value = launch_process(cmd_args, main_argv[0]);
	}
	else
	{
		cmd = malloc(sizeof(char) * (_strlen(cmd_args[0]) + 1));
		_strcpy(cmd, cmd_args[0]);
		path = get_full_path(cmd);
		free(cmd);
		if (path != NULL)
		{
			free(cmd_args[0]);
			cmd_args[0] = malloc(sizeof(char) * (_strlen(path) + 1));
			_strcpy(cmd_args[0], path);
			free(path);
			ret_value = launch_process(cmd_args, main_argv[0]);
		}
		else
		{
			free(path);
			write(STDERR_FILENO, main_argv[0], _strlen(main_argv[0]));
			write(STDERR_FILENO, ": 1: ", 5);
			write(STDERR_FILENO, cmd_args[0], _strlen(cmd_args[0]));
			write(STDERR_FILENO, ": not found\n", 12);
			ret_value = 127;
		}
	}
	return (ret_value);
}

/**
 * launch_process - execute command
 * @command: command
 * @name: name of program
 * Return: Exit code of the child process
 */
int launch_process(char **command, char *name)
{
	pid_t pid = 0;
	int status = 0;
	int exit_code = 0;

	pid = fork();
	if (pid == 0)
	{
		status = execve(command[0], command, environ);
		free_env();
		free_null_terminated_array(command);
		if (status == -1)
		{
			perror(name);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status))
		{
			exit_code = WTERMSIG(status) + 128;
		}
	}
	else
	{
		perror("fork");
	}

	return (exit_code);
}
