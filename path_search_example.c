#include "../shell.h"
#include <stdio.h>

int main(void)
{
    // Obtain the system's PATH environment variable
    char *path = get_path();
    printf("System PATH: %s\n", path);

    // Define a target command to locate in the PATH
    char *cmd = "gcc";

    // Find the full path to the target command in the system's PATH
    char *fullpath = find_in_path(cmd);

    // Print the result of the search
    if (fullpath != NULL) {
        printf("Full path for %s: %s\n", cmd, fullpath);
    } else {
        printf("Command %s not found in PATH.\n", cmd);
    }

    return (0);
}

