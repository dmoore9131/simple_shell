#include "shell.h"

int _setenv(const char *name, const char *value) {
    if (name == NULL || value == NULL) {
        fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
        return -1;
    }

    // Use the setenv function to set or update the environment variable
    if (setenv(name, value, 1) == -1) {
        perror("setenv");
        return -1;
    }

    return 0;
}

