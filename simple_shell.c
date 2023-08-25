#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];
    char *args[BUFFER_SIZE / 2]; // Array to store command and arguments
    int should_run = 1;

    while (should_run) {
        printf("$ ");
        fflush(stdout);

        // Read a line of input from the user
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            break;
        }

        // Remove the trailing newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        // Tokenize the input into command and arguments
        char *token = strtok(buffer, " ");
        int arg_count = 0;
        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; // Null-terminate the argument list

        if (arg_count > 0) {
            // Fork a child process
            pid_t pid = fork();

            if (pid < 0) {
                perror("Fork failed");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                // This code runs in the child process
                if (execvp(args[0], args) == -1) {
                    perror("Execution failed");
                    exit(EXIT_FAILURE);
                }
            } else {
                // This code runs in the parent process
                int status;
                waitpid(pid, &status, 0); // Wait for the child to finish
            }
        }
    }

    return 0;
}

