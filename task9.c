#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void execute_setenv(char *var_name, char *var_value) {
    if (setenv(var_name, var_value, 1) != 0) {
        perror("setenv");
    }
}

void execute_unsetenv(char *var_name) {
    if (unsetenv(var_name) != 0) {
        perror("unsetenv");
    }
}

int main() {
    char input[256]; // Adjust the buffer size as needed
    char *command, *var_name, *var_value;

    while (1) {
        printf("CustomShell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit on Ctrl+D or error
        }

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = 0;

        // Tokenize the input
        command = strtok(input, " ");
        var_name = strtok(NULL, " ");
        var_value = strtok(NULL, " ");

        if (command == NULL) {
            printf("No command entered.\n");
            continue;
        } else if (strcmp(command, "setenv") == 0) {
            if (var_name == NULL) {
                printf("setenv: Variable name not provided.\n");
            } else {
                execute_setenv(var_name, var_value);
            }
        } else if (strcmp(command, "unsetenv") == 0) {
            if (var_name == NULL) {
                printf("unsetenv: Variable name not provided.\n");
            } else {
                execute_unsetenv(var_name);
            }
        } else if (strcmp(command, "exit") == 0) {
            break; // Exit the shell
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    return 0;
}

