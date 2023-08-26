#include <stdio.h>
#include <stdlib.h>

int main() {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf("Enter a command: ");
        ssize_t read = getline(&line, &len, stdin);

        if (read == -1) {
            perror("getline");
            exit(EXIT_FAILURE);
        }

        printf("You entered: %s", line);
    }

    free(line);
    return 0;
}

