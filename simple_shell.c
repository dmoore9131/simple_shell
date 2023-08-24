#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * main - Entry point of the shell program
 *
 * Return: 0 on success, -1 on error
 */
int main(void)
{
    char *input_buffer = NULL;
    size_t buffer_size = 0;
    ssize_t characters_read;

    while (1)
    {
        printf("($) ");  /* Print shell prompt */
        characters_read = getline(&input_buffer, &buffer_size, stdin);

        if (characters_read == -1)
        {
            perror("Error reading input");
            free(input_buffer);
            exit(EXIT_FAILURE);
        }

        /* Process the input here (not shown in this example) */

        /* Free allocated memory */
        free(input_buffer);
    }

    return (0);
}

