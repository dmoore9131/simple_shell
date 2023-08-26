#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

// Function to print file information
void printFileStats(const char *filename) {
    struct stat fileStat;

    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return;
    }

    printf("File: %s\n", filename);
    printf("Size: %lld bytes\n", (long long)fileStat.st_size);
    printf("Mode: %o (octal)\n", fileStat.st_mode & 0777);
    printf("UID: %d\n", fileStat.st_uid);
    printf("GID: %d\n", fileStat.st_gid);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    printFileStats(filename);

    return 0;
}

