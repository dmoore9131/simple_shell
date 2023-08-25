#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];
    int should_run = 1;

    while (should_run) {
        printf("#cisfun$ ");
        fflush(stdout);

        // Read a line of input from the user
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;  // Handle Ctrl+D (EOF)
        }

        // Remove the trailing newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Fork a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
        } else if (pid == 0) {
            // This code runs in the child process
            char *command = buffer; // The command is the user input

            // Execute the command
            if (execlp(command, command, NULL) == -1) {
                perror("Execution failed");
                exit(EXIT_FAILURE);
            }
        } else {
            // This code runs in the parent process
            int status;
            waitpid(pid, &status, 0);

            // Check if the user wants to exit
            if (strcmp(buffer, "exit") == 0) {
                should_run = 0;
            }
        }
    }

    return 0;
}

