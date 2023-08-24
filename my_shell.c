#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024

int main(void) {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        printf("#cisfun$ ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\n");
            break; // Ctrl+D (end of file) was pressed
        }

        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Fork a new process
        pid_t pid = fork();

        if (pid == -1) {
            perror("Fork error");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process

            // Tokenize the input into command and arguments
            char *args[MAX_INPUT_LENGTH];
            char *token = strtok(input, " ");
            int i = 0;

            while (token != NULL) {
                args[i++] = token;
                token = strtok(NULL, " ");
            }
            args[i] = NULL;

            if (execvp(args[0], args) == -1) {
                perror("Error");
                exit(EXIT_FAILURE);
            }
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
                if (exit_status != 0) {
                    fprintf(stderr, "Command exited with status %d\n", exit_status);
                }
            } else if (WIFSIGNALED(status)) {
                int signal_number = WTERMSIG(status);
                fprintf(stderr, "Command terminated by signal %d\n", signal_number);
            }
        }
    }

    return 0;
}

