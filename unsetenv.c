#include "shell.h"

int _unsetenv(const char *name) {
    if (name == NULL) {
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return -1;
    }

    // Use the unsetenv function to remove the environment variable
    if (unsetenv(name) == -1) {
        perror("unsetenv");
        return -1;
    }

    return 0;
}

