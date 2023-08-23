#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

/* Function to tokenize a string */
void tokenize(char *input, char **tokens) {
    char *token = strtok(input, " \t\n");
    int tokenIndex = 0;

    while (token != NULL) {
        tokens[tokenIndex++] = token;
        token = strtok(NULL, " \t\n");
    }

    tokens[tokenIndex] = NULL; /* Set the last token to NULL */
}

int main(void) {
    char input[BUFFER_SIZE];
    char *tokens[BUFFER_SIZE];
    pid_t pid;

    while (1) {
        printf("($) ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; /* Exit loop on EOF */
        }

        input[strcspn(input, "\n")] = '\0'; /* Remove newline character */

        /* Tokenize input */
        tokenize(input, tokens);

        if (tokens[0] == NULL) {
            continue; /* Empty command, skip */
        }

        /* Handle built-in commands */
        if (strcmp(tokens[0], "exit") == 0) {
            exit(EXIT_SUCCESS);
        } else if (strcmp(tokens[0], "cd") == 0) {
            if (tokens[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else if (chdir(tokens[1]) != 0) {
                perror("cd");
            }
            continue;
        }

        pid = fork();
        if (pid == 0) {
            /* Child process */
            execvp(tokens[0], tokens);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            /* Parent process */
            wait(NULL);
        } else {
            perror("fork");
        }
    }

    return EXIT_SUCCESS;
}

