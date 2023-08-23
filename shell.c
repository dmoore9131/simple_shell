#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "shell.h"

char **split_line(char *line) {
    int token_index = 0;
    char *token;

    char **tokens = malloc(sizeof(char*) * MAX_TOKENS);
    if (!tokens) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " ");
    while (token) {
        tokens[token_index] = token;
        token_index++;
        token = strtok(NULL, " ");
    }

    tokens[token_index] = NULL;
    return tokens;
}

int execute_command(char **args) {
    /* TODO: Implement command execution logic using fork() and execve() */
    (void)args; /* Mark the parameter as unused */

    return 1;
}

int is_builtin(char *command) {
    /* TODO: Implement logic to check if a command is a built-in command */
    (void)command; /* Mark the parameter as unused */

    return 0;
}

void shell_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("($) ");
        line = read_line();
        args = split_line(line);
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);
}

char *read_line(void) {
    char *line = NULL;
    size_t bufsize = 0;

    if (getline(&line, &bufsize, stdin) == -1) {
        perror("read_line");
        exit(EXIT_FAILURE);
    }

    if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
    }

    return line;
}

int main(void) {
    shell_loop();
    return 0;
}

