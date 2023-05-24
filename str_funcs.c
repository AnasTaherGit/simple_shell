#include "shell.h"

/**
 * _strdup - duplicates a string
 * @str: the string to be duplicated
 * Return: pointer to the new string if successful and NULL if failed
 */
char *_strdup(char *str)
{
	unsigned int i, count;
	char *p;

	if (str == NULL)
		return (NULL);

	for (count = 0; str[count] != '\0'; count++)
		;

	p = malloc((count + 2) * sizeof(char));
	if (p == NULL)
	{
		perror("Error: malloc failed");
		return (NULL);
	}

	for (i = 0; i <= count; i++)
		p[i] = str[i];

	return (p);
}
