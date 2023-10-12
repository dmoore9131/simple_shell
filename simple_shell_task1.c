#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void) {
    char buffer[BUFFER_SIZE];
    size_t len = 0;
    pid_t child_pid;
    int status;

    while (1) {
        printf("$ ");
        fflush(stdout);

        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        len = strlen(buffer);

        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        child_pid = fork();

        if (child_pid == -1) {
            perror("Fork failed");
            exit(1);
        }

        if (child_pid == 0) {
            char *args[2];
            args[0] = buffer;
            args[1] = NULL;
            execve(buffer, args, NULL);
            perror("Command not found");
            exit(1);
        } else {
            wait(&status);
        }
    }

    return (EXIT_SUCCESS);
}
