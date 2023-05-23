#include "shell.h"

/**
 * main - Entry point for shell
 * 
 */

int main(int argc, char* argv[], char* envp[])
{
    // Load config files, if any.

    // Run command loop.
    shell_loop();

    // Perform any shutdown/cleanup.

    return EXIT_SUCCESS;
}