/* 指针加减 */

#include <stdio.h>

int main() {

    int a = 0x12345678;
    int b = 0x99991199;

    int *p1 = &a;
    char *p2 = (char *)&b;

    printf("p1 = %p, p2 = %p\n", p1, p2);
    printf("the p1+1 is %x, %x, %x\n", *(p1+1), p1[1], *p1+1);
    printf("the p2+2 is %x\n", p2[1]);

    return 0;
}
/*
output:
the p1+1 is 99991199, 99991199, 12345679
the p2+2 is 11
*/