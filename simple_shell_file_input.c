#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 32
#define MAX_VARIABLES 2

char *variables[MAX_VARIABLES] = {"$?", "$$"};
char *variable_values[MAX_VARIABLES];

int execute_command(const char *command) {
    char command_copy[MAX_INPUT_LENGTH];
    strcpy(command_copy, command);

    char *args[MAX_ARGS];
    int num_args = 0;

    char *token = strtok(command_copy, " ");
    while (token != NULL && num_args < MAX_ARGS - 1) {
        args[num_args] = token;
        token = strtok(NULL, " ");
        num_args++;
    }
    args[num_args] = NULL;

    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed");
        return -1;
    } else {
        int status;
        wait(&status);
        return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
    }
}

void initialize_variables() {
    variable_values[0] = "0"; // $? initial value
    variable_values[1] = "5104"; // $$ initial value
}

void replace_variables(char *input) {
    for (int i = 0; i < MAX_VARIABLES; i++) {
        char *var = variables[i];
        char *value = variable_values[i];
        char *pos = strstr(input, var);
        while (pos != NULL) {
            memmove(pos + strlen(value), pos + strlen(var), strlen(pos + strlen(var)) + 1);
            memcpy(pos, value, strlen(value));
            pos = strstr(pos + strlen(value), var);
        }
    }
}

void remove_comment(char *input) {
    char *comment_pos = strchr(input, '#');
    if (comment_pos != NULL) {
        *comment_pos = '\0';
    }
}

int main(int argc, char *argv[]) {
    FILE *file = NULL;
    if (argc > 1) {
        file = fopen(argv[1], "r");
        if (file == NULL) {
            perror("Error opening file");
            return 1;
        }
    }

    char input[MAX_INPUT_LENGTH];
    initialize_variables();

    while (1) {
        if (file != NULL) {
            if (fgets(input, sizeof(input), file) == NULL) {
                break;
            }
        } else {
            printf("$ ");
            fgets(input, sizeof(input), stdin);
        }
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        } else {
            remove_comment(input);
            replace_variables(input);
            int result = execute_command(input);
            variable_values[0] = result == -1 ? "1" : "0";
        }
    }

    if (file != NULL) {
        fclose(file);
    }

    return 0;
}

