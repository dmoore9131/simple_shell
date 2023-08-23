#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

void display_prompt() {
    printf("#cisfun$ ");
    fflush(stdout);
}

int main(void) {
    char input[MAX_INPUT_LENGTH];
    char *argv[2];
    int status;

    while (1) {
        display_prompt();

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break; // Handle end of file (Ctrl+D)
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Fork a child process
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            continue;
        } else if (child_pid == 0) { // Child process
            argv[0] = input;
            argv[1] = NULL;

            // Execute the command
            if (execve(input, argv, NULL) == -1) {
                perror(input); // Print an error message
                exit(EXIT_FAILURE);
            }
        } else { // Parent process
            // Wait for the child process to complete
            waitpid(child_pid, &status, 0);
        }
    }

    return EXIT_SUCCESS;
}

