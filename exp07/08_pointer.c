/* 非法访问 */

#include <stdio.h>

int main() {

    const int a = 0x12345678;
    int b = 0x11223344;

    // a = 100;
    int *p = &b;
    // *p+1
    p[1] = 0x100;

    printf("the a is %x\n", a);
    printf("the b is %x\n", b);

    return 0;
}