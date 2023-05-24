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
/**
 * _strlen - returns the length of a string
 *
 * @s: string parameter input
 *
 * Return: length of string
 */

int _strlen(char *s)
{
	int counter;

	for (counter = 0; *s != '\0'; ++s)
		++counter;

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

char *_strcpy(char *dest, char *src)
{
	int a, b = 0;

	for (a = 0; src[a] != '\0'; ++a)
	{
		dest[b] = src[a];
		++b;
	}
	dest[b] = '\0';

	return (dest);
}
/**
 * _strcat - function that concatenates
 *          two strings.
 *
 * @dest: pointer to destnation input
 * @src: pointer to source input
 *
 * Return: pointer to resulting string @dest
 */

char *_strcat(char *dest, char *src)
{
	int c, c2;

	c = 0;
	/*find the size of dest array*/
	while (dest[c])
		c++;

	/* iterate through each src array value without the null byte*/
	for (c2 = 0; src[c2]; c2++)
		/*append src[c2] to dest[c] while overwritting the null byte in dest*/
		dest[c++] = src[c2];

	return (dest);
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