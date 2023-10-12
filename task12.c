#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

#define BUFFER_SIZE 1024
#define MAX_ARGS 32

int commandExists(const char *cmd) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *path_token = strtok(path_copy, ":");

    while (path_token != NULL) {
        char cmd_path[1024];
        snprintf(cmd_path, sizeof(cmd_path), "%s/%s", path_token, cmd);
        if (access(cmd_path, X_OK) == 0) {
            free(path_copy);
            return 1;
        }
        path_token = strtok(NULL, ":");
    }

    free(path_copy);
    return 0;
}

void printEnvironment() {
    extern char **environ;
    for (char **env = environ; *env; env++) {
        printf("%s\n", *env);
    }
}

int changeDirectory(const char *dir) {
    if (chdir(dir) == -1) {
        perror("chdir");
        return -1;
    }

    if (setenv("PWD", dir, 1) == -1) {
        perror("setenv");
        return -1;
    }

    return 0;
}

int executeCommand(char **args) {
    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return -1;
    }
    if (child_pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    } else {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        }
        return -1;
    }
}

int executeLogicalOperators(char **commands, char **logical_operators, int num_commands) {
    int result = 0;
    int last_result = 0;
    for (int i = 0; i < num_commands; i++) {
        if (strcmp(logical_operators[i], "&&") == 0) {
            if (last_result == 0) {
                char *token = strtok(commands[i], " ");
                int j = 0;
                char *args[MAX_ARGS];
                while (token != NULL && j < MAX_ARGS - 1) {
                    args[j] = token;
                    j++;
                    token = strtok(NULL, " ");
                }
                args[j] = NULL;
                last_result = executeCommand(args);
            } else {
                last_result = 1; // Skip executing the command
            }
        } else if (strcmp(logical_operators[i], "||") == 0) {
            if (last_result != 0) {
                char *token = strtok(commands[i], " ");
                int j = 0;
                char *args[MAX_ARGS];
                while (token != NULL && j < MAX_ARGS - 1) {
                    args[j] = token;
                    j++;
                    token = strtok(NULL, " ");
                }
                args[j] = NULL;
                last_result = executeCommand(args);
            } else {
                last_result = 0; // Skip executing the command
            }
        }
        result = last_result;
    }
    return result;
}

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;

    while (1) {
        printf(":) ");
        if (getline(&buffer, &bufsize, stdin) == -1) {
            if (isatty(STDIN_FILENO)) {
                printf("\n");
            }
            free(buffer);
            exit(0);
        }

        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        char *token = strtok(buffer, ";");
        int num_commands = 0;
        char *commands[BUFFER_SIZE];
        char *logical_operators[BUFFER_SIZE];

        while (token != NULL) {
            commands[num_commands] = strdup(token);
            logical_operators[num_commands] = NULL;

            char *trimmed = strdup(token);
            size_t trimmed_len = strlen(trimmed);

            while (trimmed_len > 0 && (trimmed[trimmed_len - 1] == ' ' || trimmed[trimmed_len - 1] == '\t')) {
                trimmed[trimmed_len - 1] = '\0';
                trimmed_len--;
            }

            char *args[MAX_ARGS];
            char *operator = strtok(trimmed, " ");
            int i = 0;

            while (operator != NULL && i < MAX_ARGS - 1) {
                args[i] = operator;
                i++;
                operator = strtok(NULL, " ");
            }
            args[i] = NULL;

            if (i > 0) {
                if (strcmp(args[i - 1], "&&") == 0 || strcmp(args[i - 1], "||") == 0) {
                    logical_operators[num_commands] = args[i - 1];
                    args[i - 1] = NULL;
                }
            }

            num_commands++;
            token = strtok(NULL, ";");
            free(trimmed);
        }

        int result = executeLogicalOperators(commands, logical_operators, num_commands);
        printf("Exit Status: %d\n", result);

        for (int i = 0; i < num_commands; i++) {
            free(commands[i]);
        }
    }

    free(buffer);
    return 0;
}

