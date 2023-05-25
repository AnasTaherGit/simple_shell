#include "shell.h"
#include <stdbool.h>

/**
 * is_valid_number - checks if a string is a valid number
 * @string: the string to be converted
 * Return: the integer value of the converted string
 */

int is_valid_number(char *string)
{
	int index = 0;
	int sign = 1;
	int result = 0;
	bool valid = false;

	while (string[index] == ' ')
	{
		index++;
	}
	if (string[index] == '-')
	{
		sign = -1;
	}
	index++;

	while (string[index] != '\0')
	{
		if (string[index] >= '0' && string[index] <= '9')
		{
			result = result * 10 + (string[index] - '0');
			valid = true;
		}
		else
		{
			valid = false;
			break;
		}
		index++;
	}
	if (valid)
		return (result * sign);
	else
		return (-1);
}

/**
 * _strcmp - compares to strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: the difference
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int diff = 0;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		diff = s1[i] - s2[i];
		if (diff != 0)
			break;
	}
	return (diff);
}
