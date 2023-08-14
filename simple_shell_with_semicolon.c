#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 32

void execute_command(char *command) {
    char command_copy[MAX_INPUT_LENGTH];
    strcpy(command_copy, command);

    char *args[MAX_ARGS];
    int num_args = 0;

    char *token = strtok(command_copy, " ");
    while (token != NULL && num_args < MAX_ARGS - 1) {
        args[num_args] = token;
        token = strtok(NULL, " ");
        num_args++;
    }
    args[num_args] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed");
    } else {
        wait(NULL);
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];
    
    while (1) {
        printf("SimpleShell> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        char *token = strtok(input, ";");
        while (token != NULL) {
            execute_command(token);
            token = strtok(NULL, ";");
        }
    }
    
    return 0;
}

