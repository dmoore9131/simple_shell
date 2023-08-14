#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENV_VARS 100
#define MAX_INPUT_LENGTH 1024

int set_env_variable(const char *variable, const char *value) {
    if (variable == NULL || value == NULL) {
        fprintf(stderr, "setenv: Invalid arguments\n");
        return -1;
    }
    
    if (setenv(variable, value, 1) != 0) {
        fprintf(stderr, "setenv: Failed to set %s\n", variable);
        return -1;
    }
    
    return 0;
}

int unset_env_variable(const char *variable) {
    if (variable == NULL) {
        fprintf(stderr, "unsetenv: Invalid argument\n");
        return -1;
    }
    
    if (unsetenv(variable) != 0) {
        fprintf(stderr, "unsetenv: Failed to unset %s\n", variable);
        return -1;
    }
    
    return 0;
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[3];
    int num_args;
    
    while (1) {
        printf("SimpleShell> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        
        char *token = strtok(input, " ");
        num_args = 0;
        while (token != NULL && num_args < 3) {
            args[num_args] = token;
            token = strtok(NULL, " ");
            num_args++;
        }
        
        if (num_args > 0) {
            if (strcmp(args[0], "setenv") == 0) {
                if (num_args != 3) {
                    fprintf(stderr, "setenv: Incorrect number of arguments\n");
                } else {
                    if (set_env_variable(args[1], args[2]) == 0) {
                        printf("Environment variable set successfully\n");
                    }
                }
            } else if (strcmp(args[0], "unsetenv") == 0) {
                if (num_args != 2) {
                    fprintf(stderr, "unsetenv: Incorrect number of arguments\n");
                } else {
                    if (unset_env_variable(args[1]) == 0) {
                        printf("Environment variable unset successfully\n");
                    }
                }
            } else {
                printf("Unknown command: %s\n", args[0]);
            }
        }
    }
    
    return 0;
}

