#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    struct stat fileStat;

    if (stat(filename, &fileStat) < 0) {
        perror("stat");
        return 1;
    }

    printf("File Information for %s:\n", filename);
    printf("Size: %lld bytes\n", (long long)fileStat.st_size);

    return 0;
}

