#include "shell.h"

/**
 * free_error - Frees allocated memory after a system error.
 * @argv: Pointer to an array of strings to be freed.
 * @arg: Pointer to a string to be freed.
 *
 * This function is used to free memory when a system error occurs.
 */
void free_error(char **argv, char *arg)
{
    int i;

    for (i = 0; argv[i]; i++)
        free(argv[i]);
    free(argv);
    free(arg);
    exit(EXIT_FAILURE);
}

/**
 * free_tokens - Frees memory allocated by the tokenize function.
 * @ptr: Pointer to an array of strings to be freed.
 *
 * This function is used to free memory allocated by the tokenize function.
 */
void free_tokens(char **ptr)
{
    int i;

    for (i = 0; ptr[i]; i++)
        free(ptr[i]);
    free(ptr);
}

/**
 * free_path - Frees the global variable containing the PATH environment variable value.
 *
 * This function is used to free the memory allocated for the global PATH environment variable.
 */
void free_path(void)
{
    if (environ != NULL)
    {
        size_t i = 0;

        while (environ[i] != NULL)
        {
            if (_strncmp(environ[i], "PATH=", 5) == 0)
            {
                free(environ[i]);
                environ[i] = NULL;
                break;
            }
            i++;
        }
    }
}

