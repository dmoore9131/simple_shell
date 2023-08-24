#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_COUNT 64

bool handle_builtin(char **args) {
    if (strcmp(args[0], "exit") == 0) {
        exit(EXIT_SUCCESS);
    } else if (strcmp(args[0], "cd") == 0) {
        if (args[1] != NULL) {
            if (chdir(args[1]) != 0) {
                perror("cd");
            }
        }
        return true;
    }
    return false;
}

void parse_input(char *input, char **args, int *arg_count) {
    char *token; /* Move declaration to the top */
    *arg_count = 0;
    token = strtok(input, " \t\n");
    while (token != NULL && *arg_count < MAX_ARG_COUNT - 1) {
        args[(*arg_count)++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[*arg_count] = NULL;
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_COUNT];
    int arg_count;

    while (1) {
        printf("SimpleShell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';

        parse_input(input, args, &arg_count);

        if (arg_count > 0) {
            if (!handle_builtin(args)) {
                pid_t pid = fork();

                if (pid == 0) {
                    execvp(args[0], args);
                    perror("execvp");
                    exit(EXIT_FAILURE);
                } else if (pid < 0) {
                    perror("fork");
                } else {
                    wait(NULL);
                }
            }
        }
    }

    return 0;
}

