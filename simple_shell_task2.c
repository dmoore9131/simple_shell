#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    size_t len;
    char *token;
    char *args[32];
    int i = 0;
    pid_t child_pid;
    int status;

    while (1) {
        printf("$ ");

        if (getline(&buffer, &bufsize, stdin) == -1) {
            if (isatty(STDIN_FILENO)) {
                printf("\n");
            }
            free(buffer);
            exit(0);
        }

        len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        token = strtok(buffer, " ");
        i = 0;

        while (token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;

        child_pid = fork();

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
    }

    free(buffer);
    return 0;
}

