#include "shell.h"

/**
 * read_input - Read input from the standard input.
 *
 * Return: A dynamically allocated string containing the user's input.
 */
char *read_input(void)
{
    static char buffer[BUFFER_SIZE];
    static int buf_pos = 0;
    static int buf_size = 0;
    char *input_str = NULL;
    char current_char;
    int input_len = 0;

    while (1)
    {
        if (buf_pos >= buf_size)
        {
            buf_size = read(STDIN_FILENO, buffer, BUFFER_SIZE);
            buf_pos = 0;

            if (buf_size == 0)
                return input_str;
            else if (buf_size < 0)
            {
                perror("read");
                return NULL;
            }
        }

        current_char = buffer[buf_pos];
        buf_pos++;

        if (current_char == '\n')
        {
            input_str = realloc(input_str, input_len + 1);
            input_str[input_len] = '\0';
            return input_str;
        }
        else
        {
            input_str = realloc(input_str, input_len + 1);
            input_str[input_len] = current_char;
            input_len++;
        }
    }
}

