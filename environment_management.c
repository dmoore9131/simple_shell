#include "shell.h"

/**
 * set_environment_variable - Set the value of an environment variable
 * @args: Arguments (name and value of the environment variable)
 *
 * Return: 0 on success, -1 on failure
 */
int set_environment_variable(char **args)
{
    char *name, *value;

    if (args[1] == NULL || args[2] == NULL)
    {
        _puterror("Usage: setenv VARIABLE VALUE\n");
        return (-1);
    }

    name = args[1];
    value = args[2];

    if (setenv(name, value, 1) != 0)
    {
        _puterror("setenv");
        return (-1);
    }
    return (0);
}

/**
 * unset_environment_variable - Unset an environment variable
 * @args: Arguments (name of the environment variable)
 *
 * Return: 0 on success, -1 on failure
 */
int unset_environment_variable(char **args)
{
    char *name;

    if (args[1] == NULL)
    {
        _puterror("Usage: unsetenv VARIABLE\n");
        return (-1);
    }

    name = args[1];

    if (unsetenv(name) != 0)
    {
        _puterror("unsetenv");
        return (-1);
    }
    return (0);
}

