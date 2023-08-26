#include "../shell.h"
#include <stdio.h>

int main(void)
{
    // Define an input string to be tokenized
    char *input = "This is a sample input string";
    
    // Tokenize the input string
    char **tokens = tokenize_input(input);

    // Print a message indicating the testing of the tokenization function
    _puts("Testing tokenization function...\n");

    // Iterate through the tokens and print them
    for (int i = 0; tokens[i] != NULL; i++)
    {
        printf("Token %d: %s\n", i, tokens[i]);
    }

    // Free the memory used for tokens
    free_tokens(tokens);

    return 0;
}

