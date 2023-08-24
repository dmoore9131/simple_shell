#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[2]; // We will only handle commands without arguments

    while (1) {
        // Display the prompt
        printf("#cisfun$ ");

        // Read user input
        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the newline character
        input[strcspn(input, "\n")] = '\0';

        // Check if user wants to exit
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Fork a child process
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
        } else if (child_pid == 0) {
            // Child process

            // Prepare the arguments for execve
            args[0] = input;
            args[1] = NULL;

            // Execute the command
            if (execve(args[0], args, NULL) == -1) {
                perror("execve");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process

            // Wait for the child to complete
            waitpid(child_pid, NULL, 0);
        }
    }

    return 0;
}

