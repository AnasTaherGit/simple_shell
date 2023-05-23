#include "shell.h"

/**
 * split - Split a string into tokens
 * 
 * line: The string to be split
 * 
 */

Command split(char *line)
{
    char const delim = " ";
    char *saveptr;
    char *token = strtok_r(line, delim, &saveptr);
    Command cmd;

    /*Compute the occurence of delimiter */
    int count = 0;
    char *tmp=strcpy(tmp, line);

    while (tmp!='\0')
    {
        if (tmp == delim)
        {
            count++;
        }
        tmp++;
    }

    /*Allocate memory for the command*/


}