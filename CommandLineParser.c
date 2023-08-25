#include <stdio.h>

int main(int ac, char **av)
{
    int i;

    for (i = ac - 1; i >= 0; i--) {
        printf("%d. %s\n", ac - i, av[i]);
    }
    printf("%ld", getline());
    return 0;
}

