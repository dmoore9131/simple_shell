#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ALIAS_COUNT 100
#define MAX_ALIAS_LENGTH 1024

struct Alias {
    char name[MAX_ALIAS_LENGTH];
    char value[MAX_ALIAS_LENGTH];
};

struct Alias aliases[MAX_ALIAS_COUNT];
int alias_count = 0;

void print_aliases() {
    for (int i = 0; i < alias_count; i++) {
        printf("%s='%s'\n", aliases[i].name, aliases[i].value);
    }
}

void print_single_alias(const char *alias_name) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, alias_name) == 0) {
            printf("%s='%s'\n", aliases[i].name, aliases[i].value);
            return;
        }
    }
    fprintf(stderr, "Alias not found: %s\n", alias_name);
}

void define_alias(const char *alias_name, const char *alias_value) {
    for (int i = 0; i < alias_count; i++) {
        if (strcmp(aliases[i].name, alias_name) == 0) {
            strcpy(aliases[i].value, alias_value);
            return;
        }
    }
    if (alias_count < MAX_ALIAS_COUNT) {
        strcpy(aliases[alias_count].name, alias_name);
        strcpy(aliases[alias_count].value, alias_value);
        alias_count++;
    } else {
        fprintf(stderr, "Maximum alias count reached\n");
    }
}

int main() {
    char input[MAX_ALIAS_LENGTH];
    
    while (1) {
        printf("SimpleShell> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strncmp(input, "alias", 5) == 0) {
            if (strlen(input) > 6 && input[6] == ' ') {
                char *args = input + 7;
                if (args[0] != '\0') {
                    char *alias_name = strtok(args, "=");
                    char *alias_value = strtok(NULL, "");
                    if (alias_value != NULL) {
                        define_alias(alias_name, alias_value);
                    } else {
                        print_single_alias(alias_name);
                    }
                } else {
                    print_aliases();
                }
            } else {
                print_aliases();
            }
        } else {
            // Handle other commands
        }
    }
    
    return 0;
}

