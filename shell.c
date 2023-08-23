#include "shell.h"

void execute_command(char *command) {
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    
    if (child_pid == 0) {
        /* Child process */
        char *args[2];
        args[0] = command;
        args[1] = NULL;
        execve(args[0], args, NULL);
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        /* Parent process */
        wait(&status);
    }
}

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("($) ");
        read = getline(&line, &len, stdin);
        if (read == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        if (strcmp(line, "exit") == 0) {
            free(line);
            exit(EXIT_SUCCESS);
        }

        execute_command(line);
    }

    free(line);
    return 0;
}

