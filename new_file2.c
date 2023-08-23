#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>

#define MAX_INPUT_LENGTH 1024

volatile sig_atomic_t child_pid = 0;

void handle_sigint(int sig) {
    (void)sig;
    if (child_pid > 0) {
        kill(child_pid, SIGINT);
        write(STDOUT_FILENO, "\n", 1);
    }
}

void display_prompt() {
    char prompt[] = "#cisfun$ ";
    write(STDOUT_FILENO, prompt, sizeof(prompt) - 1);
}

void execute_command(char *args[]) {
    pid_t pid;

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    }

    child_pid = pid;
    waitpid(pid, NULL, 0);
    child_pid = 0;
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char *args[MAX_INPUT_LENGTH / 2 + 1];
    char *token;
    int i;
    int input_fd, output_fd;
    char *input_file = NULL;
    char *output_file = NULL;

    signal(SIGINT, handle_sigint);

    while (1) {
        display_prompt();

        if (fgets(input, sizeof(input), stdin) == NULL) {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        input[strlen(input) - 1] = '\0';

        if (strcmp(input, "exit") == 0) {
            break;
        }

        token = strtok(input, " ");
        args[0] = token;

        if (token == NULL) {
            continue;
        }

        for (i = 1; (token = strtok(NULL, " ")) != NULL; i++) {
            args[i] = token;
        }

        input_fd = STDIN_FILENO;
        output_fd = STDOUT_FILENO;

        for (i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], "<") == 0) {
                args[i] = NULL;
                token = strtok(NULL, " ");
                input_file = token;
                input_fd = open(input_file, O_RDONLY);
                if (input_fd == -1) {
                    perror("open");
                    continue;
                }
            } else if (strcmp(args[i], ">") == 0) {
                args[i] = NULL;
                token = strtok(NULL, " ");
                output_file = token;
                output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
                if (output_fd == -1) {
                    perror("open");
                    continue;
                }
            }
        }

        execute_command(args);

        if (input_fd != STDIN_FILENO) {
            close(input_fd);
        }
        if (output_fd != STDOUT_FILENO) {
            close(output_fd);
        }
    }

    return 0;
}

