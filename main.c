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

	(void)argc;
	do {
		if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
			write(STDOUT_FILENO, PROMPT, PROMPT_LEN);
		else
		{
			line = _get_input();
			command = _format_input(line);
			launch_process(command, argv[0]);
			free(line);
			return (0);
		}

		line = _get_input();
		command = _format_input(line);
		if (*command == NULL)
		{
			free(line);
			continue;
		}
		launch_process(command, argv[0]);
		free(line);

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

	if (command[1] != NULL)
	{
		errno = ENOENT;
		perror(name);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (execve(command[0], command, environ) == -1)
				perror(name);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
		}
	}
	return (1);
}
