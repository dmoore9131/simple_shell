#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

int main(void)
{
    char input[MAX_INPUT_SIZE];

    while (1)
    {
        printf("#cisfun$ "); // Display prompt
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the newline character
        input[strcspn(input, "\n")] = '\0';

        // Execute the command
        if (fork() == 0)
        {
            // Child process
            execlp(input, input, NULL); // Execute the command
            perror(input); // Print error message if exec fails
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            wait(NULL); // Wait for the child process to finish
        }
    }

    return EXIT_SUCCESS;
}

