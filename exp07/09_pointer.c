/* 指针逻辑操作 */

#include <stdio.h>

int main() {

    int a = 0x12345678;
    int b = 0x11223344;

    int *p1 = &b;
    char *p2 = (char *)&b;

    if (p1 >= p2) {
        printf("======\n");
    }
    printf("the a is %x\n", a);
    printf("the b is %x\n", b);

    return 0;
}