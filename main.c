#include "shell.h"

/**
 * main - entry point
 * Return: 0
 */

int main(void)
{
    char *line, **command;
    int status = 1;

    signal(SIGINT, handler_function);

    do
    {
        if (isatty(STDIN_FILENO))
            printf("$ ");
        else
        {
            line = _getline();
            command = _formatline(line);
            // search_and_execute(command);
            // print the command
            int i = 0;
            while (command[i] != NULL)
            {
                printf("%s\n", command[i]);
                i++;
            }
            free(line);
            free(command);
            return (0);
        }

        line = _getline();
        command = _formatline(line);

        if (*command == NULL)
        {
            free(line);
            free(command);
            continue;
        }

        // search_and_execute(command);
        // status = launch_process(command);

        

        free(line);
        free(command);

    } while (status);

    return (0);
}

/**
 * launch_process - execute command
 * @command: command
 * Return: 1
 */
int launch_process(char **command)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        if (execve(command[0], command, environ) == -1)
            perror("./shell");
    }
    else
    {
        wait(NULL);
    }

    return (1);
}

/**
 * handler_function - handle SIGINT signal
 * @signum: signal number
 */
void handler_function(int signum)
{
    if (signum == SIGINT)
    {
        write(STDOUT_FILENO, "\n$ ", strlen("\n$ "));
    }
}
