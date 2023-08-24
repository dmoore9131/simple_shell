#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    char *input;
    size_t bufsize = 32;
    input = (char *)malloc(bufsize * sizeof(char));
    if (input == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("#cisfun$ ");
        getline(&input, &bufsize, stdin);
        input[strlen(input) - 1] = '\0';  // Remove the newline character

        // Check for the "end of file" condition
        if (feof(stdin)) {
            printf("\n");
            break;
        }

        // Tokenize the input to separate command and arguments
        char *token = strtok(input, " ");
        if (token == NULL) {
            continue;  // Empty input, prompt again
        }

        // Execute the command
        if (execvp(token, &token) == -1) {
            perror("Command not found");
        }
    }

    free(input);
    return 0;
}

