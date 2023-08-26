#include "../shell.h"

int main(void)
{
    // Define arguments for testing the shell_exit function
    char *exitArgs1[] = {"exit", "0", NULL};
    char *exitArgs2[] = {"exit", "123", NULL};

    /* Test shell_exit with no arguments */
    shell_exit(exitArgs1);
    /* The shell_exit function should exit the shell with status code 0 */

    /* Test shell_exit with an argument */
    shell_exit(exitArgs2);
    /* The shell_exit function should exit the shell with status code 123 */

    return 0;
}

