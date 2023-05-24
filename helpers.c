#include "shell.h"

/**
 * _getline - get line from stdin
 * Return: line
 *
 */
char *_getline(void)
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
	if (line[characters] == '\n')
		line[characters] = '\0';
	return (line);
}

/**
 * _formatline - format line
 * @line: line
 * Return: command
 *
 */

char **_formatline(char *line)
{
	int bufsize = 64, i = 0, j = 0;
	char **tokens = malloc(bufsize * SIZEOFCHAR), *token, **temp;

	if (tokens == NULL)
	{
		perror("failed to allocate tokens\n");
		return (NULL);
	}

	token = strtok(line, TOKEN_DELIM);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += 64;
			temp = malloc(bufsize * SIZEOFCHAR);

			if (temp == NULL)
			{
				perror("failed to reallocate tokens\n");
				free(tokens);
				return (NULL);
			}

			for (j = 0; j < i; j++)
				temp[j] = tokens[j];

			free(tokens);
			tokens = temp;
		}

		token = strtok(NULL, TOKEN_DELIM);
	}
	tokens[i] = NULL;
	return (tokens);
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
