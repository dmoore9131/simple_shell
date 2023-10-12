#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include this for isatty and STDIN_FILENO

#define MAX_ALIASES 32
#define MAX_ALIAS_NAME 64
#define MAX_ALIAS_VALUE 256

struct Alias {
    char name[MAX_ALIAS_NAME];
    char value[MAX_ALIAS_VALUE];
};

struct Alias aliases[MAX_ALIASES];
int numAliases = 0;

void listAliases() {
    for (int i = 0; i < numAliases; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void printAlias(const char *name) {
    for (int i = 0; i < numAliases; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
}

int setAlias(const char *name, const char *value) {
    for (int i = 0; i < numAliases; i++) {
        if (strcmp(aliases[i].name, name) == 0) {
            strncpy(aliases[i].value, value, sizeof(aliases[i].value));
            return 0;
        }
    }
    if (numAliases < MAX_ALIASES) {
        strncpy(aliases[numAliases].name, name, sizeof(aliases[numAliases].name));
        strncpy(aliases[numAliases].value, value, sizeof(aliases[numAliases].value));
        numAliases++;
        return 0;
    }
    return -1;
}

int main(void) {
    while (1) {
        char *buffer = NULL;
        size_t bufsize = 0;
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
        if (token == NULL) {
            free(buffer);
            continue;
        }

        if (strcmp(token, "alias") == 0) {
            token = strtok(NULL, " ");
            if (token == NULL) {
                listAliases();
            } else if (strchr(token, '=') != NULL) {
                char *name = strtok(token, "=");
                char *value = strtok(NULL, "");
                if (name != NULL && value != NULL) {
                    if (setAlias(name, value) == -1) {
                        printf("Alias limit exceeded.\n");
                    }
                }
            } else {
                do {
                    printAlias(token);
                    token = strtok(NULL, " ");
                } while (token != NULL);
            }
        } else {
            // Handle other commands
            printf("This is not an alias command. You entered: %s\n", buffer);
        }

        free(buffer);
    }

    return 0;
}

