#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include string.h for strlen

#define BUFFER_SIZE 1024

int main() {
    char command[BUFFER_SIZE];

    printf("Enter a command: ");
    if (fgets(command, sizeof(command), stdin) != NULL) {
        command[strlen(command) - 1] = '\0'; // Remove newline character
        printf("You entered: %s\n", command);
    }

    return 0;
}

