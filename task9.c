
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_setenv(char *command) {
    char *var_name = strtok(NULL, " "); // Parse the environment variable name
    char *var_value = strtok(NULL, " "); // Parse the environment variable value

    if (var_name == NULL) {
        fprintf(stderr, "Usage: setenv <variable_name> [variable_value]\n");
    } else {
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
    }
}

void execute_unsetenv(char *command) {
    char *var_name = strtok(NULL, " "); // Parse the environment variable name

    if (var_name == NULL) {
        fprintf(stderr, "Usage: unsetenv <variable_name>\n");
    } else {
        if (unsetenv(var_name) != 0) {
            perror("unsetenv");
        }
    }
}

int main() {
    char command[100]; // Define a buffer to read user input
    while (1) {
        printf("Enter a command: ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; // Exit on EOF (e.g., Ctrl+D)
        }

        // Remove the trailing newline character from the input
        size_t len = strlen(command);
        if (len > 0 && command[len - 1] == '\n') {
            command[len - 1] = '\0';
        }

        // Check the first word to determine the command
        char *token = strtok(command, " ");
        if (token == NULL) {
            fprintf(stderr, "Invalid command\n");
            continue;
        }

        if (strcmp(token, "setenv") == 0) {
            execute_setenv(command);
        } else if (strcmp(token, "unsetenv") == 0) {
            execute_unsetenv(command);
        } else {
            fprintf(stderr, "Invalid command\n");
        }
    }

    return 0;
}

