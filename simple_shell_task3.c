#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 32

int commandExists(const char *cmd) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *path_token = strtok(path_copy, ":");

    while (path_token != NULL) {
        char cmd_path[1024];
        snprintf(cmd_path, sizeof(cmd_path), "%s/%s", path_token, cmd);
        if (access(cmd_path, X_OK) == 0) {
            free(path_copy);
            return 1;
        }
        path_token = strtok(NULL, ":");
    }

    free(path_copy);
    return 0;
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    char *args[MAX_ARGS];
    int status;

    while (1) {
        printf(":) ");
        if (getline(&buffer, &bufsize, stdin) == -1) {
            if (isatty(STDIN_FILENO)) {
                printf("\n");
            }
            free(buffer);
            exit(0);
        }

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        char *token = strtok(buffer, " ");
        int i = 0;

        while (token != NULL && i < MAX_ARGS - 1) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }

        if (i > 0) {
            args[i] = NULL;

            if (commandExists(args[0])) {
                pid_t child_pid = fork();
                if (child_pid == -1) {
                    perror("fork");
                    exit(1);
                }
                if (child_pid == 0) {
                    execvp(args[0], args);
                    perror("execvp");
                    exit(1);
                } else {
                    wait(&status);
                }
            } else {
                printf("Command not found: %s\n", args[0]);
            }
        }
    }

    free(buffer);
    return 0;
}

