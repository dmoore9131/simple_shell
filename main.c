#include "shell.h"

int main(void)
{
    char *input;
    char **args;

    while (1)
    {
        input = get_input(); // Implement this function to get user input
        args = split_input(input); // Implement this function to split input into arguments
        execute(args); // Implement this function to execute commands
        free(input);
        free(args);
    }

    return (0);
}

