#include "shell.h"

/**
 * get_path - Get the value of the PATH environment variable.
 *
 * Return: A pointer to the value of the PATH environment variable.
 */
char *get_path(void)
{
    return (_getenv("PATH"));
}

