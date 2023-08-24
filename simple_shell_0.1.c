#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void display_prompt() {
    printf("($) ");
    fflush(stdout);
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[100];  // Assuming a maximum of 100 arguments
    int status;
    
    while (1) {
        display_prompt();
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }
        
        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0';
        
        // Tokenize the input into arguments
        char *token = strtok(input, " ");
        int arg_count = 0;
        while (token != NULL) {
            args[arg_count] = token;
            token = strtok(NULL, " ");
            arg_count++;
        }
        args[arg_count] = NULL;  // Null-terminate the argument list
        
        // Fork a child process to execute the command
        pid_t child_pid = fork();
        if (child_pid == -1) {
            perror("fork");
        } else if (child_pid == 0) {
            // This code runs in the child process
            if (execvp(args[0], args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        } else {
            // This code runs in the parent process
            waitpid(child_pid, &status, 0);
        }
    }
    
    return 0;
}

