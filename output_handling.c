#include "shell.h"

/**
 * print_string - Prints a string to the standard output stream
 * @str: The string to print
 *
 * Return: Void
 */
void print_string(char *str)
{
    size_t len;
    ssize_t num_written;

    len = _strlen(str);
    num_written = write(STDOUT_FILENO, str, len);
    if (num_written == -1)
    {
        perror("write");
    }
}

/**
 * print_error - Prints an error message to the standard error stream
 * @err: The error message to print
 *
 * Return: Void
 */
void print_error(char *err)
{
    size_t len;
    ssize_t num_written;

    len = _strlen(err);
    num_written = write(STDERR_FILENO, err, len);
    if (num_written == -1)
    {
        perror("write");
    }
}

