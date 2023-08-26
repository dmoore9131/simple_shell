#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("Number of command-line arguments: %d\n", argc);

    // Print each command-line argument
    for (int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}

