#include "shell.h"

/**
 * main - Entry point for a simple shell
 *
 * Return: EXIT_SUCCESS upon successful execution.
 */
int main(void)
{
    char *input;
    char **args;
    int status;

    /* Register signal handlers */
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);
    signal(SIGTSTP, sigtstp_handler);

    do {
        input = get_input();
        if (!input || !*input) /* EOF detected, exit the loop */
            break;

        args = tokenize_input(input);
        if (!args || !*args) {
            free(input);
            free_tokens(args);
            continue;
        }

        status = execute(args);
        free(input);
        free_tokens(args);

        /* Set status to 1 to continue the loop */
        status = 1;
    } while (status);

    return (EXIT_SUCCESS);
}

