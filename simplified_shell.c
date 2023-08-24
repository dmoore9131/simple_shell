#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Function to handle built-in commands
int handle_builtin(char *command) {
    if (strcmp(command, "exit") == 0) {
        exit(EXIT_SUCCESS);  // Gracefully exit the shell
    }
    return 0;  // Not a built-in command
}

int main() {
    char input[BUFFER_SIZE];

    while (1) {
        printf("#cisfun$ ");
        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            // Handle Ctrl+D (end of file)
            printf("\n");
            break;
        }

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Check for built-in commands
        if (handle_builtin(input) == 0) {
            // Fork a new process
            pid_t pid = fork();

            if (pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) {
                // Child process
                char *args[] = {input, NULL};
                execvp(input, args);

                // If execvp fails
                perror(input);
                exit(EXIT_FAILURE);
            } else {
                // Parent process
                int status;
                waitpid(pid, &status, 0);

                if (WIFEXITED(status)) {
                    int exit_status = WEXITSTATUS(status);
                    printf("Exit status: %d\n", exit_status);
                }
            }
        }
    }

    return 0;
}

