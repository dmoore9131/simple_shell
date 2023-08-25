#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char *input = NULL;
    size_t input_size = 0;

    while (1)
    {
        // Display the prompt
        printf("#cisfun$ ");

        // Read user input
        ssize_t bytes_read = getline(&input, &input_size, stdin);

        // Handle end of file (Ctrl+D)
        if (bytes_read == -1)
        {
            if (feof(stdin))
            {
                printf("\n"); // Print a newline for a clean exit
                free(input);
                exit(EXIT_SUCCESS);
            }
            else
            {
                perror("getline"); // Handle other errors
                free(input);
                exit(EXIT_FAILURE);
            }
        }

        // Remove the newline character from the input
        if (bytes_read > 0 && input[bytes_read - 1] == '\n')
            input[bytes_read - 1] = '\0';

        // Execute the command
        pid_t child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork");
            free(input);
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) // Child process
        {
            // Execute the command using execvp
            char *args[] = {input, NULL};
            if (execvp(input, args) == -1)
            {
                perror("execvp");
                free(input);
                exit(EXIT_FAILURE);
            }
        }
        else // Parent process
        {
            // Wait for the child to complete
            int status;
            waitpid(child_pid, &status, 0);

            if (WIFEXITED(status))
            {
                // Child process exited normally
                int exit_status = WEXITSTATUS(status);
                printf("Exit status: %d\n", exit_status);
            }
            else if (WIFSIGNALED(status))
            {
                // Child process was terminated by a signal
                int term_signal = WTERMSIG(status);
                printf("Terminated by signal: %d\n", term_signal);
            }
        }
    }

    free(input);
    return (0);
}

