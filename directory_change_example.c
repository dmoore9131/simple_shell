#include "../shell.h"

int main(void)
{
    // Get the current working directory and print it
    char *currentDir = _getenv("PWD");
    printf("Current directory: %s\n", currentDir);

    // Change the directory to its parent directory
    char *changeDirArgs[] = {"cd", "..", NULL};
    shell_cd(changeDirArgs);

    // Get and print the updated current working directory
    currentDir = _getenv("PWD");
    printf("Current directory after change: %s\n", currentDir);

    // Your code continues here...

    return 0;
}

