#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define PROMPT "#cisfun$ "

int main() {
    char command[MAX_COMMAND_LENGTH];
    
    while (1) {
        printf(PROMPT);
        if (fgets(command, sizeof(command), stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Remove the newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Handle exit command
        if (strcmp(command, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        // Create a child process
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            int ret = execlp(command, command, NULL);

            if (ret == -1) {
                perror("execvp");
                exit(1);
            }
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) != 0) {
                    printf("Child process exited with status %d\n", WEXITSTATUS(status));
                }
            }
        }
    }

    return 0;
}

