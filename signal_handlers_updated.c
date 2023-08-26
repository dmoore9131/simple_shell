#include "shell.h"

/**
 * sigint_handler - Handles the SIGINT signal (Ctrl+C).
 * @sig: Signal number
 *
 * This function is called when the SIGINT signal is received, typically when
 * the user presses Ctrl+C. It prints a newline character to start a new line
 * and then displays the shell prompt again.
 */
void sigint_handler(int sig)
{
    (void)sig; // Unused parameter
    _putchar('\n'); // Print a newline character
    prompt(); // Display the shell prompt
}

/**
 * sigquit_handler - Handles the SIGQUIT signal (Ctrl+\).
 * @sig: Signal number
 *
 * This function is called when the SIGQUIT signal is received, typically when
 * the user presses Ctrl+\ (backslash). It prints an error message indicating
 * that the program was terminated with a core dump and then exits the shell
 * with a successful status code.
 */
void sigquit_handler(int sig)
{
    (void)sig; // Unused parameter
    _puterror("Quit (core dumped)\n"); // Print an error message
    exit(EXIT_SUCCESS); // Exit the shell with a successful status code
}

/**
 * sigtstp_handler - Handles the SIGTSTP signal (Ctrl+Z).
 * @sig: Signal number
 *
 * This function is called when the SIGTSTP signal is received, typically when
 * the user presses Ctrl+Z. It prints a newline character to start a new line
 * and then displays the shell prompt again.
 */
void sigtstp_handler(int sig)
{
    (void)sig; // Unused parameter
    _putchar('\n'); // Print a newline character
    prompt(); // Display the shell prompt
}

