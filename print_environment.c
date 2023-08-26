#include "shell.h"

/**
 * print_environment - Print all the environment variables.
 *
 * Description: This function prints all the environment variables to the
 * standard output.
 *
 * Return: 0 on success.
 */
int print_environment(void)
{
    int i;

    for (i = 0; environ[i]; i++)
    {
        _puts(environ[i]);
        _putchar('\n');
    }

    return (0);
}

