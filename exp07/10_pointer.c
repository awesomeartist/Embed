#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {    

    int a = 10;
    int *p1 = &a;
    int **p2 = &p1;
    char *str[5];
    char ch1 = 'h', ch2 = 'e';

    str[0] = &ch1;
    str[1] = &ch2;
    printf("str = %s, str[0] = %lu, *str[0] = %c\n", str[0], str[0], *str[0]);

    printf("a = %d\np1 = %lu\np2 = %lu\n", **p2, *p2, p2);
    for(int i=0; i<argc; i++) {
         printf("the argv[%d] is %s\n", i, argv[i]); 
    }

    return 0;
}