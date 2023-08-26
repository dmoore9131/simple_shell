#include "../shell.h"

int main(void)
{
    // Define arguments for testing environment variable manipulation
    char *setEnvArgs[] = {"setenv", "MYVAR", "hello", NULL};
    char *unsetEnvArgs[] = {"unsetenv", "MYVAR", NULL};

    /* Set an environment variable */
    if (shell_setenv(setEnvArgs) == -1)
    {
        fprintf(stderr, "Failed to set environment variable\n");
        exit(EXIT_FAILURE);
    }

    /* Get the value of the environment variable */
    char *value = getenv("MYVAR");
    if (value == NULL)
    {
        fprintf(stderr, "Failed to get environment variable\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(value, "hello") != 0)
    {
        fprintf(stderr, "Unexpected environment variable value: %s\n", value);
        exit(EXIT_FAILURE);
    }

    /* Unset the environment variable */
    if (shell_unsetenv(unsetEnvArgs) == -1)
    {
        fprintf(stderr, "Failed to unset environment variable\n");
        exit(EXIT_FAILURE);
    }

    /* Try to get the value of the environment variable again */
    value = getenv("MYVAR");
    if (value != NULL)
    {
        fprintf(stderr, "Environment variable was not unset\n");
        exit(EXIT_FAILURE);
    }

    // All tests passed
    printf("All tests passed\n");
    return EXIT_SUCCESS;
}

