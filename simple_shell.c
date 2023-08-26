#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_INPUT_LEN 1024

char *args[] = {"/bin/sh", "-c", NULL};

void read_line(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) == NULL) {
        printf("\n");
        exit(EXIT_SUCCESS); /* Ctrl+D (EOF) was entered */
    }
}

void execute_command(char *command) {
    pid_t pid, wpid;
    int status;

    args[2] = command;  /* Update the command in the args array */

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        /* Child process */
        if (execve(args[0], args, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main(void) {
    char buffer[MAX_INPUT_LEN];

    while (1) {
        printf("$ "); /* Display the prompt */
        read_line(buffer, sizeof(buffer));

        /* Remove the newline character if it exists */
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting the shell...\n");
            exit(EXIT_SUCCESS);
        }

        execute_command(buffer);
    }

    return EXIT_SUCCESS;
}

