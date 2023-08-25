#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/** 
 * main - run program 
 *
 * @argc: Number of command-line arguments
 * @argv: Array of command-line argument strings
 * 
 * Return: 0. 
 */
int main(int argc, char *argv[])
{
    int i;
    pid_t pid = getpid(); // Get the process ID of the current process
    pid_t ppid = getppid(); // Get the parent process ID

    printf("Parent Process ID: %d\n", ppid); // Print the parent process ID
    printf("Current Process ID: %d\n", pid); // Print the current process ID

    for (i = 0; i < argc; i++)
    {
        printf("Argument %d: %s\n", i, argv[i]); // Print command-line arguments
    }

    return 0;
}

