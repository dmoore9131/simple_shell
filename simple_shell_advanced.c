#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

static char buffer[BUFFER_SIZE];
static size_t buffer_pos = 0;
static size_t buffer_size = 0;

ssize_t custom_read(int fd, void *buf, size_t count) {
    if (buffer_pos >= buffer_size) {
        buffer_size = read(fd, buffer, BUFFER_SIZE);
        buffer_pos = 0;

        if (buffer_size == -1) {
            perror("read");
            return -1;
        } else if (buffer_size == 0) {
            return 0; 
        }
    }

    size_t bytes_to_read = buffer_size - buffer_pos;
    if (bytes_to_read > count) {
        bytes_to_read = count;
    }

    memcpy(buf, buffer + buffer_pos, bytes_to_read);
    buffer_pos += bytes_to_read;

    return bytes_to_read;
}

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
    if (*lineptr == NULL || *n == 0) {
        *n = BUFFER_SIZE;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL) {
            perror("malloc");
            return -1;
        }
    }

    size_t i = 0;
    while (1) {
        char c;
        ssize_t ret = custom_read(fileno(stream), &c, 1);

        if (ret == -1) {
            return -1;
        } else if (ret == 0) {
            if (i == 0) {
                return -1; 
            } else {
                break;
            }
        }

        if (c == '\n') {
            (*lineptr)[i] = '\0';
            break;
        }

        (*lineptr)[i] = c;
        i++;

        if (i >= *n) {
            *n *= 2;
            *lineptr = (char *)realloc(*lineptr, *n);
            if (*lineptr == NULL) {
                perror("realloc");
                return -1;
            }
        }
    }

    return i;
}

void execute_command(char *command) {
    pid_t pid = fork();

    if (pid == 0) { 
        char *argv[64]; 
        int argc = 0;

        char *token = strtok(command, " ");
        while (token != NULL) {
            argv[argc] = token;
            argc++;

            if (argc >= 64) {
                fprintf(stderr, "Too many arguments.\n");
                exit(1);
            }

            token = strtok(NULL, " ");
        }

        argv[argc] = NULL;

        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    } else if (pid > 0) { 
        int status;
        waitpid(pid, &status, 0);
    } else { 
        perror("fork");
    }
}

int main() {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf("SimpleShell> ");
        ssize_t read = custom_getline(&line, &len, stdin);

        if (read == -1) {
            break; 
        }

        
        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
            read--;
        }

        if (strcmp(line, "exit") == 0) {
            break; 
        }

        execute_command(line);
    }

    free(line);
    return 0;
}

