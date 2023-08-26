#include "../shell.h"
#include <stdio.h>

int main(void)
{
    // Print a message indicating the testing of the get_input function
    printf("Testing the get_input function...\n");

    // Get user input
    char *input = get_input();

    // Print the received input
    printf("User Input: %s\n", input);

    // Free the allocated memory
    free(input);

    return 0;
}

