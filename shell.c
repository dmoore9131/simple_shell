#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        printf("#cisfun$ "); // Display prompt

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Remove the trailing newline character if present
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting shell.\n");
            break; // Exit the loop
        }

        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {
            // This code is executed by the child process
            // Replace the child process with the desired command
            execlp(input, input, NULL);
            // If execlp returns, it means an error occurred
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // This code is executed by the parent process
            int status;
            wait(&status); // Wait for the child process to finish

            if (WIFEXITED(status)) {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            } else {
                printf("Child process did not exit normally\n");
            }
        }
    }

    return 0;
}

