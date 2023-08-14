#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 1024

void handle_exit(char *status_str) {
    int status = atoi(status_str);
    exit(status);
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[64];

    while (1) {
        printf("$ ");
        fgets(input, sizeof(input), stdin);

        input[strcspn(input, "\n")] = '\0';

        char *token = strtok(input, " ");
        int arg_count = 0;

        while (token != NULL) {
            args[arg_count] = token;
            arg_count++;
            token = strtok(NULL, " ");
        }

        args[arg_count] = NULL;

        if (arg_count > 0 && strcmp(args[0], "exit") == 0) {
            if (arg_count > 1) {
                handle_exit(args[1]);
            } else {
                handle_exit("0");
            }
        }

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("Error executing command");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            perror("Error forking");
        } else {
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}

