#include <stdio.h>
#include <stdlib.h>

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Enter a line of text: ");
    
    // Use getline to read a line from stdin
    read = getline(&line, &len, stdin);

    if (read != -1) {
        printf("You entered: %s", line);
    } else {
        printf("Error reading input.");
    }

    // Free allocated memory
    free(line);
    return 0;
}

