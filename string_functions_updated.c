#include "shell.h"

/**
 * custom_putchar - Write a character to stdout.
 * @ch: The character to print.
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char ch)
{
    return (write(1, &ch, 1));
}

/**
 * custom_strspn - Get the length of a prefix substring.
 * @str: Pointer to the input string.
 * @prefix: Substring prefix to look for.
 *
 * Return: The number of bytes in the initial segment.
 */
unsigned int custom_strspn(char *str, char *prefix)
{
    unsigned int i, j;

    for (i = 0; str[i]; i++)
    {
        for (j = 0; prefix[j]; j++)
        {
            if (str[i] == prefix[j])
                break;
        }
        if (!prefix[j])
            return (i);
    }

    return (i);
}

