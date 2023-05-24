#include "shell.h"

/**
 * main - entry point
 * @argc: number of arguments
 * @argv: arguments
 * Return: 0
 */

int main(int argc, char **argv)
{

	char *line = NULL;
	char **command = NULL;
	int status = 1;

	(void)argc;
	do {
		if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
			write(STDOUT_FILENO, PROMPT, PROMPT_LEN);
		else
		{
			line = _get_input();
			command = _get_tokens(line, TOKEN_DELIM);
			cmd_handle(command, argv);
			free(command);
			free(line);
			return (0);
		}

		line = _get_input();
		command = _get_tokens(line, TOKEN_DELIM);
		if (*command == NULL)
		{
			free(command);
			free(line);
			continue;
		}
		cmd_handle(command, argv);
		free(command);
		free(line);

	} while (status);

	return (0);
}
