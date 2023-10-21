#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ENV_VAR_LENGTH 128
#define MAX_ENV_VALUE_LENGTH 256
#define MAX_BUFFER_SIZE 1024
#define MAX_ARG_COUNT 32

int commandExists(const char *cmd);
void printEnvironment(void);
void setEnvironmentVariable(const char *var, const char *value);
void unsetEnvironmentVariable(const char *var);

int main(void) {
    char *buffer = NULL;
    size_t bufsize = 0;
    char *args[MAX_ARG_COUNT];
    int status;

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

        char *token = strtok(buffer, " ");
        int i = 0;

        while (token != NULL && i < MAX_ARG_COUNT - 1) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }

        if (i > 0) {
            args[i] = NULL;

            if (strcmp(args[0], "exit") == 0) {
                if (args[1] != NULL) {
                    int exit_status = atoi(args[1]);
                    free(buffer);
                    exit(exit_status);
                } else {
                    free(buffer);
                    exit(0);
                }
            } else if (strcmp(args[0], "env") == 0) {
                printEnvironment();
            } else if (strcmp(args[0], "setenv") == 0) {
                if (i == 3) {
                    setEnvironmentVariable(args[1], args[2]);
                } else {
                    fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                }
            } else if (strcmp(args[0], "unsetenv") == 0) {
                if (i == 2) {
                    unsetEnvironmentVariable(args[1]);
                } else {
                    fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                }
            } else if (commandExists(args[0])) {
                pid_t child_pid = fork();
                if (child_pid == -1) {
                    perror("fork");
                    exit(1);
                }
                if (child_pid == 0) {
                    execvp(args[0], args);
                    perror("execvp");
                    exit(1);
                } else {
                    wait(&status);
                }
            } else {
                printf("Command not found: %s\n", args[0]);
            }
        }
    }

    free(buffer);
    return 0;
}

int commandExists(const char *cmd) {
    char *path = getenv("PATH");
    char *path_copy = strdup(path);
    char *path_token = strtok(path_copy, ":");

    while (path_token != NULL) {
        char cmd_path[MAX_BUFFER_SIZE];
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

void setEnvironmentVariable(const char *var, const char *value) {
    if (setenv(var, value, 1) == -1) {
        fprintf(stderr, "Failed to set environment variable\n");
    }
}

void unsetEnvironmentVariable(const char *var) {
    if (unsetenv(var) == -1) {
        fprintf(stderr, "Failed to unset environment variable\n");
    }
}

