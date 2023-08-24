#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

void display_prompt() {
    printf("#cisfun$ ");
    fflush(stdout);
}

int main() {
    char input[MAX_INPUT_SIZE];
    int status;

    while (1) {
        display_prompt();

        if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove the newline character
        input[strcspn(input, "\n")] = '\0';

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork error");
        } else if (pid == 0) {
            // Child process
            if (execlp(input, input, (char *)NULL) == -1) {
                // Try with the full path to the command
                if (execlp("/bin/ls", "/bin/ls", (char *)NULL) == -1) {
                    perror("Command not found");
                    exit(EXIT_FAILURE);
                }
            }
        } else {
            // Parent process
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

