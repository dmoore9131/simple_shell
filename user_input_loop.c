#include "../shell.h"

int main(void)
{
    char *input_str;

    while (1)
    {
        // Prompt the user for input and store it in input_str
        input_str = get_line();

        // Check for errors in getting input
        if (input_str == NULL)
        {
            perror("get_line");
            exit(EXIT_FAILURE);
        }

        // Check if the user wants to exit
        if (strcmp(input_str, "exit") == 0)
            break;

        // Print the user's input
        printf("You entered: %s\n", input_str);

        // Free the memory used for input_str
        free(input_str);
    }

    printf("Goodbye!\n");
    return 0;
}

