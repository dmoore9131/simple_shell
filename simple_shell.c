#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

// Function to execute a command
void execute_command(char *command) {
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // This code is executed by the child process
        // Replace the child process with the desired command
        execlp(command, command, NULL);

        // If execlp returns, it means an error occurred
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // This code is executed by the parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        printf("#cisfun$ "); // Display prompt

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            perror("fgets");
            exit(EXIT_FAILURE);
        }

        // Remove the trailing newline character if present
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            printf("Exiting shell.\n");
            break; // Exit the loop
        }

        execute_command(input);
    }

    return 0;
}

