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
        printf("#cisfun$ "); // Display prompt
        fflush(stdout);

        // Read a line of input from the user
        if (fgets(input, sizeof(input), stdin) == NULL) {
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
            // Tokenize the input for commands and arguments
            char *args[BUFFER_SIZE / 2];
            char *token = strtok(input, " ");
            int arg_count = 0;

            while (token != NULL) {
                args[arg_count] = token;
                arg_count++;
                token = strtok(NULL, " ");
            }

            args[arg_count] = NULL; // Null-terminate the argument list

            // Execute the command
            if (execvp(args[0], args) == -1) {
                perror("Execution failed");
                exit(EXIT_FAILURE);
            }
        } else {
            // This code runs in the parent process
            int status;
            waitpid(pid, &status, 0); // Wait for the child process to finish
        }
    }

    return 0;
}

