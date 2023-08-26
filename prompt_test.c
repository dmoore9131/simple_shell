#include "../shell.h"
#include <stdio.h>

int main(void)
{
    // Print a message indicating the testing of the prompt function
    _puts("Testing the prompt function...\n");

    // Call the prompt function to simulate user input
    prompt();

    // Print a newline to separate the output
    _puts("\n");

    return 0;
}

