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
	ssize_t characters = 0;

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
 * @delimiters: delimiters
 * Return: command
 *
 */

char **_get_tokens(char *line, const char *delimiters)
{
	char **command = NULL, *token = NULL, *tmp = NULL;
	int token_count = 0, i = 0, j = 0;

	token_count = count_tokens(line, delimiters);
	command = malloc(sizeof(char *) * (token_count + 1));
	if (command == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, delimiters);
	for (i = 0; i < token_count; i++)
	{
		tmp = _strdup(token);
		command[i] = malloc(sizeof(char) * (_strlen(tmp) + 1));
		if (command[i] == NULL)
		{
			perror("malloc");
			for (j = 0; j < i; j++)
				free(command[j]);
			free(command);
			exit(EXIT_FAILURE);
		}
		_strcpy(command[i], tmp);
		free(tmp);
		token = strtok(NULL, delimiters);
	}
	command[token_count] = NULL;
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
 * @sig : signal
 */
void handler_function(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, handler_function);
	write(STDIN_FILENO, new_prompt, 3);
}
