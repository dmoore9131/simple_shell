#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void execute_setenv(char *command) {
    char *token = strtok(NULL, " "); // Parse the command
    if (token == NULL) {
        fprintf(stderr, "Usage: setenv <variable_name> [variable_value]\n");
    } else {
        char *var_name = strdup(token);
        char *var_value = strtok(NULL, " "); // Parse the environment variable value

        if (var_value != NULL) {
            if (setenv(var_name, var_value, 1) != 0) {
                perror("setenv");
            }
        } else {
            // Handle the case where only the variable name is provided
            if (setenv(var_name, "", 1) != 0) {
                perror("setenv");
            }
        }
        free(var_name); // Clean up memory
    }
}

void execute_unsetenv(char *command) {
    char *token = strtok(NULL, " "); // Parse the command
    if (token == NULL) {
        fprintf(stderr, "Usage: unsetenv <variable_name>\n");
    } else {
        char *var_name = strdup(token);

        if (unsetenv(var_name) != 0) {
            perror("unsetenv");
        }
        free(var_name); // Clean up memory
    }
}

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

        // Check for built-in commands and execute them
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

