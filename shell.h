#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

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



#endif
