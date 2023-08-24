#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> // Add this line

#define BUFFER_SIZE 1024

void display_prompt() {
    printf("#cisfun$ ");
}

void execute_command(const char *command) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        if (execlp(command, command, (char *)NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    } else {
        int status;
        wait(&status);
    }
}

int main(void) {
    char buffer[BUFFER_SIZE];
    while (1) {
        display_prompt();
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }
        buffer[strlen(buffer) - 1] = '\0';
        execute_command(buffer);
    }
    return 0;
}

