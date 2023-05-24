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
	int characters = 0;

	characters = getline(&line, &bufsize, stdin);
	if (characters == -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(EXIT_SUCCESS);
	}
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

	int bufsize = 64, i = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token, *saveptr;
	char **temp;

	if (tokens == NULL)
	{
		perror("failed to allocate tokens\n");
		return (NULL);
	}

	token = strtok_r(line, TOKEN_DELIM, &saveptr);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;

		if (i >= bufsize)
		{
			bufsize += 64;
			temp = realloc(tokens, bufsize * sizeof(char *));

			if (temp == NULL)
			{
				perror("failed to reallocate tokens\n");
				free(tokens);
				return (NULL);
			}
			tokens = temp;
		}

		token = strtok_r(NULL, TOKEN_DELIM, &saveptr);
	}
	tokens[i] = NULL;
	return (tokens);
}
