#include "shell.h"

/**
 * _get_input - get line from stdin
 * Return: line
 *
 */
char *_get_input(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters;

	signal(SIGINT, handler_function);

	characters = getline(&line, &bufsize, stdin);
	if (characters == -1)
	{
		if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
			write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(EXIT_SUCCESS);
	}

	return (line);
}

/**
 * _get_tokens - format line
 * @line: line
 * Return: command
 *
 */

char **_get_tokens(char *line)
{
	char **command = NULL;
	char *token = NULL;
	int token_count, i;

	token_count = count_tokens(line, TOKEN_DELIM);

	command = malloc(sizeof(char *) * (token_count + 1));
	if (command == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, TOKEN_DELIM);
	for (i = 0; i < token_count; i++)
	{
		command[i] = token;
		token = strtok(NULL, TOKEN_DELIM);
	}
	command[token_count] = NULL;

	free(token);
	return (command);
}

/**
 * count_tokens - count tokens
 * @line: line
 * @delimiter: delimiter
 * Return: count
 */
int count_tokens(char *line, const char *delimiter)
{
	int count = 0;
	char *line_copy = _strdup(line);
	char *token = strtok(line_copy, delimiter);

	while (token != NULL)
	{
		count++;
		token = strtok(NULL, delimiter);
	}

	free(line_copy);
	return (count);
}
/**
 * handler_function - handle SIGINT signal
 * @signum: signal number
 */
void handler_function(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_SUCCESS);
	}
}
