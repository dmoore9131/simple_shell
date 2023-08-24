#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void display_prompt() {
    printf("$ "); // Display a basic shell prompt
}

int main() {
    char buffer[BUFFER_SIZE];
    char *args[BUFFER_SIZE / 2];
    int should_run = 1;

    while (should_run) {
        display_prompt();

        // Read user input
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break; // Exit if end-of-file (Ctrl+D) is encountered
        }

        // Tokenize the input into arguments
        int arg_count = 0;
        char *token = strtok(buffer, " \t\n");
        while (token != NULL) {
            args[arg_count] = token;
            token = strtok(NULL, " \t\n");
            arg_count++;
        }
        args[arg_count] = NULL; // Null-terminate the argument list

        // Handle exit command
        if (strcmp(args[0], "exit") == 0) {
            should_run = 0;
            continue;
        }

        // Create a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
            exit(1);
        } else if (pid == 0) {
            // Child process executes the command
            execvp(args[0], args);
            perror("Execution failed"); // If execvp returns, there was an error
            exit(1);
        } else {
            // Parent process waits for the child to complete
            wait(NULL);
        }
    }

    return 0;
}

