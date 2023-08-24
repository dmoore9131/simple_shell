#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char buffer[BUFFER_SIZE];
    char *args[] = {"/bin/ls", NULL};  // Command and arguments for the ls command

    while (1) {
        printf("#cisfun$ ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character

        if (strcmp(buffer, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork error");
            exit(1);
        } else if (pid == 0) {  // Child process
            execvp(args[0], args);  // Execute the ls command
            perror("execvp");
            exit(1);
        } else {  // Parent process
            wait(NULL);  // Wait for the child process to finish
        }
    }

    return 0;
}

