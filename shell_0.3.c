#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

// Function to parse input into arguments
int parse_input(char *input, char **args) {
    int argc = 0;
    char *token = strtok(input, " \t\n");
    
    while (token != NULL) {
        args[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[argc] = NULL;
    
    return argc;
}

// Function to execute the command
void execute_command(char **args) {
    execvp(args[0], args);
    perror("Error executing command");
    exit(EXIT_FAILURE);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    
    while (1) {
        printf(":) ");
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break; // Exit on Ctrl+D (EOF)
        }

        input[strcspn(input, "\n")] = '\0'; // Remove trailing newline
        
        int argc = parse_input(input, args);

        if (argc > 0) {
            // Check if the command exists in the PATH
            if (access(args[0], X_OK) == 0) {
                pid_t pid = fork();
                
                if (pid == -1) {
                    perror("Fork error");
                } else if (pid == 0) {
                    // Child process
                    execute_command(args);
                } else {
                    // Parent process
                    wait(NULL);
                }
            } else {
                printf("%s: command not found\n", args[0]);
            }
        }
    }

    printf("\n");
    return 0;
}

