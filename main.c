#include "shell.h"

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: arguments
 * Return: 0
 */

int main(int argc, char **argv)
{
	
	char *line, **command;
	int status = 1;
	
	(void) argc;
	do {
		if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
			write(STDOUT_FILENO, "$ ", 2);
		else
		{
			line = _getline();
			command = _formatline(line);
			launch_process(command, argv[0]);
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
		launch_process(command, argv[0]);
		free(line);
		free(command);

	} while (status);

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
	pid_t pid;
	char **command_no_args = malloc(2 * SIZEOFCHAR);

	command_no_args[0] = command[0];
	command_no_args[1] = NULL;
	if (command[1] != NULL)
	{
		errno = ENOENT;
		perror(name);
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			perror(name);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(command[0], command_no_args, environ) == -1)
				perror(name);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
		}
	}
	free(command_no_args);
	return (1);
}
