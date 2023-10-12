#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *my_getline(void) {
    static char buffer[BUFFER_SIZE];
    static size_t index = 0;
    static ssize_t bytes_read = 0;

    if (index >= bytes_read) {
        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytes_read <= 0) {
            return NULL;  // No more input or error
        }
        index = 0;
    }

    char *line = NULL;
    size_t line_length = 0;

    while (index < bytes_read) {
        char current_char = buffer[index];
        index++;

        if (current_char == '\n' || current_char == '\0') {
            if (line_length > 0) {
                line = (char *)realloc(line, line_length + 1);
                line[line_length] = '\0';
                return line;
            }
        } else {
            line = (char *)realloc(line, line_length + 2);
            line[line_length] = current_char;
            line[line_length + 1] = '\0';
            line_length++;
        }
    }

    return line;
}

int main(void) {
    while (1) {
        char *input = my_getline();
        if (input == NULL) {
            printf("No more input or an error occurred.\n");
            break;
        }
        printf("You entered: %s\n", input);
        free(input);
    }

    return 0;
}

