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
	int status = 1, ret_value = 0;

	(void)argc;
	do {
		if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
			write(STDOUT_FILENO, PROMPT, PROMPT_LEN);

		line = _get_input();
		if (line == NULL)
		{
			status = 0;
			continue;
		}
		command = _get_tokens(line, TOKEN_DELIM);
		free(line);
		if (*command == NULL)
		{
			free_null_terminated_array(command);
			continue;
		}
		ret_value = cmd_handle(command, argv);
		free_null_terminated_array(command);

	} while (status);

	return (ret_value);
}
