#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 100

// Function to execute a command
void executeCommand(char *command) {
    if (system(command) == -1) {
        printf("Error: Command execution failed.\n");
    }
}

int main() {
    char input[MAX_COMMAND_LENGTH];

    while (1) {
        printf("#cisfun$ "); // Display the shell prompt
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n"); // Handle Ctrl+D (end of file)
            break;
        }

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break; // Exit the shell
        }

        executeCommand(input); // Execute the user's command
    }

    return 0;
}

