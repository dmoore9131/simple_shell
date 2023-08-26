#include "../shell.h"

int main(void)
{
    // Declare an array to store command line arguments
    char **args;
    
    // Define the command to execute
    char *cmd = "env";

    // Tokenize the input command
    args = tokenize_input(cmd);

    // Check if tokenization was successful
    if (args == NULL || *args == NULL)
    {
        fprintf(stderr, "Failed to tokenize input\n");
        return (EXIT_FAILURE);
    }

    // Execute the command and check for errors
    if (execute(args) != 0)
    {
        fprintf(stderr, "Failed to execute command: %s\n", cmd);
        free_tokens(args);
        return (EXIT_FAILURE);
    }

    // Free the memory used for tokenized arguments
    free_tokens(args);

    // Return success
    return (EXIT_SUCCESS);
}

