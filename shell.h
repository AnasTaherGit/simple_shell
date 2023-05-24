#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define TOKEN_DELIM " \t\r\n\a"

/**
 * Command - Struct for a command
 *
 * cmd: The command
 * argc: The number of arguments
 * argv: The arguments
 */

typedef struct Command
{
    char *cmd;
    int argc;
    char **argv;
} Command;

extern char **environ;

char *_getline(void);
char **_formatline(char *line);

#endif