#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void execute_setenv(char *command);
void execute_unsetenv(char *command);

int main(void) {
    char *input;
    size_t len = 0;
    ssize_t read;

    while (1) {
        printf("#cisfun$ ");
        read = getline(&input, &len, stdin);

        if (read == -1) {
            perror("getline");
            free(input);
            exit(EXIT_FAILURE);
        }

        if (strncmp(input, "setenv", 6) == 0) {
            execute_setenv(input);
        } else if (strncmp(input, "unsetenv", 8) == 0) {
            execute_unsetenv(input);
        } else {
            // Handle other commands or external programs here
        }

        free(input);
        input = NULL;
    }

    return 0;
}

void execute_setenv(char *command) {
    char *tokens = strtok(command, " ");
    char *name = strtok(NULL, " ");
    char *value = strtok(NULL, " ");

    if (name == NULL) {
        fprintf(stderr, "Usage: setenv <variable_name> [variable_value]\n");
        return;
    }

    if (value != NULL) {
        if (setenv(name, value, 1) != 0) {
            perror("setenv");
        }
    } else {
        if (setenv(name, "", 1) != 0) {
            perror("setenv");
        }
    }
}

void execute_unsetenv(char *command) {
    char *tokens = strtok(command, " ");
    char *name = strtok(NULL, " ");

    if (name == NULL) {
        fprintf(stderr, "Usage: unsetenv <variable_name>\n");
        return;
    }

    if (unsetenv(name) != 0) {
        perror("unsetenv");
    }
}

