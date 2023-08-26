#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = getpid(); // Get the process ID of the current process
    printf("Process ID: %d\n", pid);

    return 0;
}

