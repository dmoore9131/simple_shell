
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

// Function to execute a command
void execute_command(char *command) {
    pid_t pid;
    int status;

    pid = fork(); // Create a new process

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // This is the child process
        char *args[] = {command, NULL};

        // Try to execute the command, and if it fails, print an error
        if (execvp(command, args) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else { // This is the parent process
        // Wait for the child process to finish
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    char buffer[BUFFER_SIZE];
    
    while (1) {
        printf("#cisfun$ "); // Print a simple prompt
        
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            // Handle Ctrl+D (end of file)
            printf("\n");
            break;
        }
        
        // Remove the trailing newline character
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        
        // Execute the command
        execute_command(buffer);
    }

    return 0;
}

