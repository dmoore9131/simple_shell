#include "../myshell.h"
#include <stdio.h>

int main(void)
{
    /* Get the current working directory */
    char *dir = myshell_getenv("PWD");
    printf("Current directory: %s\n", dir);

    /* Change directory to the parent directory */
    char *args[] = {"cd", "..", NULL};
    myshell_cd(args);

    /* Attempt to change to a non-existent directory */
    char *args3[] = {"cd", "_test_", NULL};
    myshell_cd(args3);

    /* Get the current working directory again */
    dir = myshell_getenv("PWD");
    printf("Current directory: %s\n", dir);

    /* Set a custom environment variable */
    args[0] = "setenv";
    args[1] = "MYVAR";
    args[2] = "myvalue";
    args[3] = NULL;
    myshell_setenv(args);

    /* Get the value of the environment variable */
    char *value = getenv("MYVAR");
    if (value == NULL)
    {
        fprintf(stderr, "Failed to get environment variable\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(value, "myvalue") != 0)
    {
        fprintf(stderr, "Unexpected environment variable value: %s\n", value);
        exit(EXIT_FAILURE);
    }

    /* Unset the custom environment variable */
    args[0] = "unsetenv";
    args[1] = "MYVAR";
    args[2] = NULL;
    myshell_unsetenv(args);

    /* Attempt to get the value of the environment variable again */
    value = getenv("MYVAR");
    if (value != NULL)
    {
        fprintf(stderr, "Environment variable was not unset\n");
        exit(EXIT_FAILURE);
    }

    printf("All setenv and unsetenv tests passed\n");

    /* Exit the shell */
    args[0] = "exit";
    args[1] = NULL;
    myshell_exit(args);

    return 0;
}

