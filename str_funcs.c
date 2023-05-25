#include "shell.h"

/**
 * _strdup - duplicates a string
 * @str: the string to be duplicated
 * Return: pointer to the new string if successful and NULL if failed
 */
char *_strdup(const char *str)
{
	size_t length = _strlen(str);
	char *duplicate = NULL;

	if (str == NULL)
	{
		return (NULL);
	}

	duplicate = malloc((length + 1) * sizeof(char));
	if (duplicate == NULL)
	{
		perror("Error: malloc failed");
		return (NULL);
	}

	_strcpy(duplicate, str);
	return (duplicate);
}
/**
 * _strlen - returns the length of a string
 *
 * @s: string parameter input
 *
 * Return: length of string
 */

size_t _strlen(const char *s)
{
	size_t counter = 0;

	if (s == NULL)
	{
		return (0);
	}
	while (*s != '\0')
	{
		++counter;
		++s;
	}

	return (counter);
}
/**
 * _strcpy - copies a string from one pointer to another
 *	including the terminating null byte (\0)
 *
 * @src: source of string parameter input
 * @dest: destination of string
 *
 * Return: pointer to dest input parameter
 */

char *_strcpy(char *dest, const char *src)
{
	int i = 0;
	if (dest == NULL || src == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
/**
 * _strcat - function that concatenates
 *          two strings.
 *
 * @destination: pointer to destination input
 * @source: pointer to source input
 *
 * Return: pointer to resulting string @dest
 */

char *_strcat(char *destination, char *source)
{
	char *ptr = destination;

	while (*ptr != '\0')
	{
		ptr++;
	}

	while (*source != '\0')
	{
		*ptr = *source;
		ptr++;
		source++;
	}

	*ptr = '\0';

	return (destination);
}
/**
 * _strncmp - compares two strings up to n characters
 * @s1: the first string
 * @s2: the second string
 * @n: number of characters to compare
 *
 * Return: the difference
 */

int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i;
	int diff;

	for (i = 0; i < n; i++)
	{
		diff = s1[i] - s2[i];
		if (diff != 0)
			break;
	}
	return (diff);
}
