#include <stdio.h>

int main() {

    int a[100];
    // char *a[100];   // sizeof(a) = 100*4
    // char **a;
    printf("the size of a is %lu\n", sizeof(a));

    return 0;
}