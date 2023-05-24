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
#define PATH_DELIM ":"
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

/*main*/
int main(int argc, char **argv);

/*command_handler*/
int cmd_handle(char **cmd_args, char *line, char **main_argv);
int launch_process(char **command, char *name);

/*free*/
void free_array(char **array, int size);

/*helpers.c*/
char *_get_input(void);
char **_get_tokens(char *line, const char *delimiter);
int count_tokens(char *line, const char *delimiter);
void handler_function(int signum);

/*path_helpers.c*/
char *build_cmd_path(char *dir, char *cmd);
char **get_path_directories(char *path_env);
char *get_full_path(char *cmd);
char *_getenv(char *var_name);

/*str_funcs.c*/
char *_strdup(const char *str);
size_t _strlen(const char *s);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _strncmp(char *s1, char *s2, size_t n);
int _atoi(char *s);
int _strcmp(char *s1, char *s2);

/*builtins.c*/
int check_builtins(char **cmd_args, char *line);
int _exit_builtin(char **cmd_args, char *line);

#endif
