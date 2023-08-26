#include "../shell.h"
#include <stdio.h>

int main(void)
{
    // Print a message to indicate testing the execute function
    printf("Testing execute function...\n");

    // Get user input
    char *input = get_input();

    // Tokenize the user input into arguments
    char **args = tokenize_input(input);

    // Execute the command specified by the user
    execute(args);

    // Free allocated memory
    free(input);
    free_tokens(args);

    return 0;
}

