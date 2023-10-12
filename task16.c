#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_VARIABLES 2

struct Variable {
    char name[16];
    char value[256];
};

struct Variable variables[MAX_VARIABLES];

void initializeVariables() {
    for (int i = 0; i < MAX_VARIABLES; i++) {
        variables[i].name[0] = '\0';
        variables[i].value[0] = '\0';
    }
}

char *getVariableValue(const char *name) {
    for (int i = 0; i < MAX_VARIABLES; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    return NULL;
}

void setVariable(const char *name, const char *value) {
    for (int i = 0; i < MAX_VARIABLES; i++) {
        if (variables[i].name[0] == '\0') {
            strncpy(variables[i].name, name, sizeof(variables[i].name));
            strncpy(variables[i].value, value, sizeof(variables[i].value));
            return;
        } else if (strcmp(variables[i].name, name) == 0) {
            strncpy(variables[i].value, value, sizeof(variables[i].value));
            return;
        }
    }
}

int main(int argc, char *argv[]) {
    initializeVariables();

    if (argc == 2) {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("File open error");
            return 1;
        }

        char *buffer = NULL;
        size_t bufsize = 0;
        ssize_t bytesRead;

        while ((bytesRead = getline(&buffer, &bufsize, file)) != -1) {
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
            }

            char *command = strdup(buffer);
            char *token = strtok(buffer, " ");

            if (token != NULL) {
                if (strcmp(token, "exit") == 0) {
                    free(buffer);
                    free(command);
                    break;
                } else if (strcmp(token, "echo") == 0) {
                    token = strtok(NULL, " ");
                    if (token != NULL && token[0] == '$') {
                        if (strcmp(token, "$?") == 0) {
                            printf("0\n");
                        } else if (strcmp(token, "$$") == 0) {
                            printf("%d\n", getpid());
                        } else {
                            char *value = getVariableValue(token + 1);
                            if (value != NULL) {
                                printf("%s\n", value);
                            }
                        }
                    } else {
                        printf("%s\n", command + 5);
                    }
                } else if (strcmp(token, "export") == 0) {
                    token = strtok(NULL, " ");
                    if (token != NULL) {
                        char *name = strdup(token);
                        token = strtok(NULL, " ");
                        if (token != NULL) {
                            setVariable(name, token);
                        }
                        free(name);
                    }
                }
            }

            free(command);
        }

        free(buffer);
        fclose(file);
    }

    return 0;
}

