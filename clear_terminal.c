#include "shell.h"

/**
 * clear_terminal - Clears the terminal screen.
 * @args: An array of arguments (unused).
 *
 * Description: This function clears the terminal screen by sending the ANSI
 * escape codes for clearing the screen and moving the cursor to the home
 * position.
 *
 * Return: 1 to continue executing, or 0 to exit.
 */
int clear_terminal(char **args)
{
    (void)args; /* Avoid "unused parameter" warning */
    _puts("\033[2J\033[H"); /* ANSI escape codes for clearing screen and moving cursor */
    return (1);
}

