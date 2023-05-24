#include "shell.h"

/**
 * main - entry point
 * Return: 0
 */

int main(void)
{
	char *line, **command;
	int status = 1;

	signal(SIGINT, handler_function);
	do {
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "($) ", 5);
		else
		{
			line = _getline();
			command = _formatline(line);
			launch_process(command);
			free(line);
			free(command);
			return (0);
		}

		line = _getline();
		command = _formatline(line);

		if (*command == NULL)
		{
			free(line);
			free(command);
			continue;
		}

		launch_process(command);

		free(line);
		free(command);

	} while (status);

	return (0);
}

/**
 * launch_process - execute command
 * @command: command
 * Return: 1
 */
int launch_process(char **command)
{
	pid_t pid;
	char **command_no_args = malloc(2 * SIZEOFCHAR);

	command_no_args[0] = command[0];
	command_no_args[1] = NULL;
	if (command[1] != NULL)
	{
		errno = ENOENT;
		perror("./shell");
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(command[0], command_no_args, environ) == -1)
				perror("./shell");
		}
		else
		{
			wait(NULL);
		}
	}
	free(command_no_args);
	return (1);
}

/**
 * handler_function - handle SIGINT signal
 * @signum: signal number
 */
void handler_function(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 2);
		exit(EXIT_SUCCESS);
	}
}
