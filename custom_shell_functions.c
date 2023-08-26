#include "custom_shell.h"

/**
 * custom_prompt - Display a custom shell prompt.
 */
void custom_prompt(void);

/**
 * custom_get_input - Get custom user input.
 *
 * Return: A pointer to the user's input string.
 */
char *custom_get_input(void);

/**
 * custom_free_last_input - Free memory used by the last input.
 */
void custom_free_last_input(void);

/**
 * custom_execute_command - Execute a custom shell command.
 * @command: The command to execute.
 *
 * Return: 1 if the command was executed successfully, otherwise 0.
 */
int custom_execute_command(char *command);

/**
 * custom_handle_sigint - Handle the SIGINT signal (Ctrl+C).
 * @signal: The signal number.
 *
 * This function is called when the SIGINT signal is received, typically when
 * the user presses Ctrl+C. It processes the signal and takes appropriate action.
 */
void custom_handle_sigint(int signal);

/**
 * custom_handle_sigquit - Handle the SIGQUIT signal (Ctrl+\).
 * @signal: The signal number.
 *
 * This function is called when the SIGQUIT signal is received, typically when
 * the user presses Ctrl+\ (backslash). It prints an error message and terminates
 * the shell gracefully.
 */
void custom_handle_sigquit(int signal);

/**
 * custom_handle_sigstp - Handle the SIGTSTP signal (Ctrl+Z).
 * @signal: The signal number.
 *
 * This function is called when the SIGTSTP signal is received, typically when
 * the user presses Ctrl+Z. It prints a newline character and then displays the
 * custom shell prompt again.
 */
void custom_handle_sigstp(int signal);

/**
 * custom_display_help - Display custom shell help information.
 */
void custom_display_help(void);

/**
 * custom_shell_exit - Exit the custom shell.
 */
void custom_shell_exit(void);

/**
 * custom_shell_cd - Change the current directory in the custom shell.
 */
void custom_shell_cd(void);

/**
 * custom_set_environment - Set a custom environment variable.
 */
void custom_set_environment(void);

/**
 * custom_unset_environment - Unset a custom environment variable.
 */
void custom_unset_environment(void);

/**
 * custom_display_environment - Display the custom environment variables.
 */
void custom_display_environment(void);

