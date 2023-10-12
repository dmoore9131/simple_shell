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
        while (token != NULL) {
            char *trimmed = strdup(token);
            size_t trimmed_len = strlen(trimmed);

            while (trimmed_len > 0 && (trimmed[trimmed_len - 1] == ' ' || trimmed[trimmed_len - 1] == '\t')) {
                trimmed[trimmed_len - 1] = '\0';
                trimmed_len--;
            }

            char *args[MAX_ARGS];
            char *token = strtok(trimmed, " ");
            int i = 0;

            while (token != NULL && i < MAX_ARGS - 1) {
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
                    if (args[1] != NULL && args[2] != NULL) {
                        if (setenv(args[1], args[2], 1) == -1) {
                            fprintf(stderr, "Failed to set environment variable\n");
                        }
                    } else {
                        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
                    }
                } else if (strcmp(args[0], "unsetenv") == 0) {
                    if (args[1] != NULL) {
                        if (unsetenv(args[1]) == -1) {
                            fprintf(stderr, "Failed to unset environment variable\n");
                        }
                    } else {
                        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
                    }
                } else if (strcmp(args[0], "cd") == 0) {
                    if (args[1] == NULL) {
                        const char *home_dir = getenv("HOME");
                        if (home_dir == NULL) {
                            fprintf(stderr, "cd: HOME not set\n");
                        } else {
                            if (changeDirectory(home_dir) == 0) {
                                chdir(home_dir);
                            }
                        }
                    } else if (strcmp(args[1], "-") == 0) {
                        const char *old_dir = getenv("OLDPWD");
                        if (old_dir == NULL) {
                            fprintf(stderr, "cd: OLDPWD not set\n");
                        } else {
                            if (changeDirectory(old_dir) == 0) {
                                chdir(old_dir);
                            }
                        }
                    } else {
                        if (changeDirectory(args[1]) == 0) {
                            chdir(args[1]);
                        }
                    }
                } else if (commandExists(args[0])) {
                    int result = executeCommand(args);
                    if (result == -1) {
                        fprintf(stderr, "Command failed: %s\n", args[0]);
                    }
                } else {
                    fprintf(stderr, "Command not found: %s\n", args[0]);
                }
            }

            free(trimmed);
            token = strtok(NULL, ";");
        }
    }

    free(buffer);
    return 0;
}

