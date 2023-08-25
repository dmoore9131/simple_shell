#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char input[BUFFER_SIZE];
    int should_run = 1;

    while (should_run) {
        printf("#cisfun$ "); /* Display prompt */
        fflush(stdout);

        // Read a line of input from the user
        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // This code runs in the child process
            if (execlp(input, input, NULL) == -1) {
                perror("Execution failed");
                exit(EXIT_FAILURE);
            }
        } else {
            // This code runs in the parent process
            wait(NULL); // Wait for the child process to finish
        }
    }

    return 0;
}

