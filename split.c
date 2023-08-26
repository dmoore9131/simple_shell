#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "Write a function";
    char *token;

    token = strtok(str, " ");

    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }

    return 0;
}

