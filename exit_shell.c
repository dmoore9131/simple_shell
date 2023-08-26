#include "shell.h"

/**
 * exit_shell - Exit the shell.
 * @args: Arguments.
 *
 * Description: This function allows the user to exit the shell with an
 * optional status code.
 *
 * Return: Nothing.
 */
void exit_shell(char **args)
{
    int status = 0;

    if (args[1] != NULL)
    {
        status = _atoi(args[1]);
    }

    free_tokens(args);
    free_last_input();
    exit(status);
}

