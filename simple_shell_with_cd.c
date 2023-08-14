#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 1024

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[2]; // Command + Argument
    
    while (1) {
        printf("SimpleShell> ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        
        char *token = strtok(input, " ");
        int num_args = 0;
        while (token != NULL && num_args < 2) {
            args[num_args] = token;
            token = strtok(NULL, " ");
            num_args++;
        }
        
        if (num_args > 0) {
            if (strcmp(args[0], "cd") == 0) {
                if (num_args == 1) {
                    const char *home_dir = getenv("HOME");
                    if (home_dir != NULL) {
                        if (chdir(home_dir) == 0) {
                            setenv("PWD", home_dir, 1);
                        } else {
                            perror("cd");
                        }
                    } else {
                        fprintf(stderr, "cd: Could not find home directory\n");
                    }
                } else if (num_args == 2) {
                    if (strcmp(args[1], "-") == 0) {
                        const char *prev_dir = getenv("OLDPWD");
                        if (prev_dir != NULL) {
                            if (chdir(prev_dir) == 0) {
                                setenv("PWD", prev_dir, 1);
                            } else {
                                perror("cd");
                            }
                        } else {
                            fprintf(stderr, "cd: Could not find previous directory\n");
                        }
                    } else {
                        if (chdir(args[1]) == 0) {
                            setenv("OLDPWD", getenv("PWD"), 1);
                            setenv("PWD", args[1], 1);
                        } else {
                            perror("cd");
                        }
                    }
                }
            } else {
                // Handle other commands
            }
        }
    }
    
    return 0;
}

