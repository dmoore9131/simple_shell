#include "../shell.h"
#include <stdio.h>

int main(void)
{
    // Define a string
    char *str = "The quick brown fox jumps over the lazy dog.";

    // Print the original string
    printf("Original String: %s\n", str);

    // Calculate and print the length of the string
    printf("Length of String: %zu\n", _strlen(str));

    // Create a copy of the string
    char *copy = _strdup(str);
    printf("Copy of String: %s\n", copy);
    free(copy);

    // Concatenate a new string to the original string
    char *concatenated = _strcat(str, " And another sentence.");
    printf("Concatenated String: %s\n", concatenated);
    free(concatenated);

    // Find and print a substring in the original string
    char *substring = _strstr(str, "fox jumps");
    if (substring != NULL) {
        printf("Substring: %s\n", substring);
    } else {
        printf("Substring not found.\n");
    }

    return 0;
}

