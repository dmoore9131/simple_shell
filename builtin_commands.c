#include "shell.h"

/**
 * is_builtin - Check if the command is a built-in shell command.
 * @command: The command to check.
 *
 * Return: 1 if the command is a built-in, 0 otherwise.
 */
int is_builtin(char *command)
{
    if (!command)
        return 0;
    
    if (!_strcmp(command, "exit") || !_strcmp(command, "env") ||
        !_strcmp(command, "setenv") || !_strcmp(command, "unsetenv") ||
        !_strcmp(command, "help") || !_strcmp(command, "cd") ||
        !_strcmp(command, "clear"))
    {
        return 1;
    }

    return 0;
}

/**
 * execute_builtin - Execute a built-in shell command.
 * @command: The built-in command.
 * @args: The arguments for the command.
 *
 * Return: 1 if the command is executed successfully, 0 otherwise.
 */
int execute_builtin(char *command, char **args)
{
    if (!_strcmp(command, "exit"))
    {
        shell_exit(args);
        return 1;
    }
    else if (!_strcmp(command, "env"))
    {
        shell_env();
        return 1;
    }
    else if (!_strcmp(command, "setenv"))
    {
        return shell_setenv(args);
    }
    else if (!_strcmp(command, "unsetenv"))
    {
        return shell_unsetenv(args);
    }
    else if (!_strcmp(command, "help"))
    {
        shell_help();
        return 1;
    }
    else if (!_strcmp(command, "cd"))
    {
        shell_cd(args);
        return 1;
    }
    else if (!_strcmp(command, "clear"))
    {
        shell_clear(args);
        return 1;
    }

    return 0;
}

