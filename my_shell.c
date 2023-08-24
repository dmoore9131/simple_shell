#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void display_prompt() {
    printf("($) ");
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    pid_t pid;

    while (1) {
        display_prompt();

        if (fgets(command, sizeof(command), stdin) == NULL) {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        /* Remove the newline character from the end of the command */
        command[strcspn(command, "\n")] = '\0';

        /* Check if the user wants to exit */
        if (strcmp(command, "exit") == 0) {
            break;
        }

        /* Fork a child process */
        pid = fork();

        if (pid == -1) {
            perror("fork");
        }
        else if (pid == 0) {
            /* Child process */
            /* Create an array to hold the command and arguments */
            char *args[2];
            args[0] = command;
            args[1] = NULL;

            /* Execute the command using execvp */
            if (execvp(command, args) == -1) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
        else {
            /* Parent process */
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

