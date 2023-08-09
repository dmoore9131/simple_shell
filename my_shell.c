#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void display_prompt(void) {
    printf(":) ");
}

int main(void) {
    char input[MAX_INPUT_SIZE];
    
    while (1) {
        display_prompt();
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            if (feof(stdin)) {
                printf("\n");
                break; // End of file (Ctrl+D)
            }
            perror("fgets");
            exit(EXIT_FAILURE);
        }
        
        input[strcspn(input, "\n")] = '\0'; // Remove newline character
        
        char *args[MAX_INPUT_SIZE];
        int arg_count = 0;
        
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        args[arg_count] = NULL; // Null-terminate the array
        
        if (args[0] != NULL) {
            pid_t child_pid = fork();
            if (child_pid == -1) {
                perror("fork");
                exit(EXIT_FAILURE);
            } else if (child_pid == 0) {
                // Child process
                if (execvp(args[0], args) == -1) {
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
            } else {
                // Parent process
                int status;
                if (waitpid(child_pid, &status, 0) == -1) {
                    perror("waitpid");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    
    return 0;
}

