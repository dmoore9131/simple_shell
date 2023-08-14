
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

void read_input(char *input) {
    printf("Shell > ");
    fgets(input, MAX_INPUT_LENGTH, stdin);
    input[strlen(input) - 1] = '\0'; 
}

int parse_input(char *input, char **args) {
    int argc = 0;
    char *token = input;
    
    while (*token != '\0') {
        while (*token == ' ' || *token == '\t') {
            *token++ = '\0'; 
        }
        
        if (*token != '\0') {
            args[argc++] = token;
            while (*token != ' ' && *token != '\t' && *token != '\0') {
                token++;
            }
        }
    }
    args[argc] = NULL;
    
    return argc;
}

int execute_command(char **args) {
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("Fork error");
        return -1;
    } else if (pid == 0) {
        if (execvp(args[0], args) == -1) {
            perror("Execution error");
            exit(EXIT_FAILURE);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        return status;
    }
    return 0;
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    
    while (1) {
        read_input(input);
        int argc = parse_input(input, args);
        
        if (argc > 0) {
            if (strcmp(args[0], "exit") == 0) {
                exit(EXIT_SUCCESS);
            }
            execute_command(args);
        }
    }
    
    return 0;
}

