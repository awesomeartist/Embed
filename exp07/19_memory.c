#include <stdio.h>

int fun() {
    static int a = 0x10;
    printf("in fun, the address of a is %p\n", &a);
    return a++;
}

int main(void) {
    
    static int a;
    unsigned char *p1;
    char *p2 = "helao world!";  // 存放在只读空间数据段
    const int b = 0x12345678;

    printf("the size of a is %lu\n", sizeof(a));
    printf("the size of b is %lu\n", sizeof(b));
    printf("the size of p1 is %lu\n", sizeof(p1));

    a = 0x10;
    p1 = (unsigned char*)main;
    fun();
    printf("the main is %p\n", main);
    printf("in main, the &a is   %p\n", &a);     // %p 输出指针变量
    printf("in main, the &b is   %p\n", &b);
    printf("the p2 is %s\n", p2);
    printf("the string address is %p\n", "helao world!");
    p2[3] = 'l';    // 只读空间不可修改，段错误


    printf("the  *p1 is %d\n", *p1);
    *p1 = 0x12;                         // 段错误
    printf("the *p1 is %d\n", *p1);

    return 0;
}