#include "shell.h"

/**
 * change_directory - Change the current working directory of the shell.
 * @args: An array of arguments (usually containing the directory path).
 *
 * Description: This function changes the current working directory of the
 * shell to the specified directory. If no argument is provided, it changes
 * to the HOME directory.
 */
void change_directory(char **args)
{
    char *dir = args[1];
    int ret;

    /* If no argument is provided, change to HOME directory */
    if (dir == NULL)
    {
        dir = _getenv("HOME");
        if (dir == NULL)
        {
            _puts("cd: No HOME directory found\n");
            return;
        }
    }

    ret = chdir(dir);
    if (ret == -1)
    {
        perror("cd");
    }
}

