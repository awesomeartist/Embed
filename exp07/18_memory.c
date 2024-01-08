#include <stdio.h>

int b = 10;     // 全局数据空间，已初始化，存放在 data 区域

int fun() {
    static int a = 0x10;    // 全局数据空间，已初始化，存放在 data 区域，但是与外部的 a 有区分
    return a++;
}

int main(void) {
    
    static int a = 10;     // 全局数据空间，未初始化存放在 bss 区域
    unsigned char *p1;

    printf("the size of a is %lu\n", sizeof(a));
    printf("the size of b is %lu\n", sizeof(b));
    printf("the size of p1 is %lu\n", sizeof(p1));
    
    p1 = (unsigned char*)main;
    printf("the &a is   %p\n", &a);     // %p 输出指针变量
    printf("the &b is   %p\n", &b);

    printf("the  *p1 is %d\n", *p1);

    return 0;
}