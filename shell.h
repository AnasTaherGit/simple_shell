#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define TOKEN_DELIM " \t\r\n\a"
#define SIZEOFCHAR sizeof(char *)

#define PROMPT "$ "
#define PROMPT_LEN 2

/**
 * struct Node - Struct for a node
 * @token: The token
 * @next: The next node
 * Description: Struct for a node
 */

typedef struct Node
{
	char *token;
	struct Node *next;
} Node;

/**
 * struct Command - Struct for a command
 *
 * @cmd: The command
 * @argc: The number of arguments
 * @argv: The arguments
 *
 * Description: Struct for a command
 */

typedef struct Command
{
	char *cmd;
	int argc;
	char **argv;
} Command;

extern char **environ;

char *_get_input(void);
char **_format_input(char *line);
int count_tokens(char *line, const char *delim);
int launch_process(char **command, char *name);
void handler_function(int signum);
int process_user_input(char *input, char **commands_args, char *name);

void iter_free(char **array);

char *_strdup(char *str);

#endif
