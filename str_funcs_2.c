#include "shell.h"

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: the integer value of the converted string
 */
int _atoi(char *string)
{
    int x;
    int res = 0;
    int sign = -1;
    int brk = 0;

    for (x = 0; string[x] != '\0'; x++)
    {
        if (string[x] == '-')
        {
            sign = sign * -1;
        }
        if (string[x] >= '0' && string[x] <= '9')
        {
            res = res * 10;
            res -= (string[x] - '0');
            brk = 1;
        }
        else if (brk == 1)
            break;
    }
    res = sign * res;
    return (res);
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
    int i, diff;

    for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
    {
        diff = s1[i] - s2[i];
        if (diff != 0)
            break;
    }
    return (diff);
}
