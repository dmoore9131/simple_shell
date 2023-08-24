
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    printf("Parent PID: %u\n", getppid());

    FILE *fp = fopen("/proc/sys/kernel/pid_max", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    unsigned int max_pid;
    fscanf(fp, "%u", &max_pid);
    fclose(fp);

    printf("Maximum PID: %u\n", max_pid);

    printf("Enter a message: ");
    char input[100];
    fgets(input, sizeof(input), stdin);
    printf("You entered: %s", input);

    char input_copy[100];
    strcpy(input_copy, input);

    char *token = strtok(input_copy, " ");
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, " ");
    }

    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        return 1;
    }

    printf("My PID: %u\n", getpid());
    if (child_pid == 0) {
        printf("I am the child process\n");
        char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};
        execve(argv[0], argv, NULL);
        perror("execve");
        return 1;
    } else {
        printf("I am the parent process\n");
        printf("Parent process waiting...\n");
        int status;
        wait(&status);
        printf("Parent process resumed.\n");
    }

    return 0;
}

