// 实参传递给实参的方式：拷贝（不论是值传递还是地址传递，本质都是拷贝）
// 本质是对内存的拷贝，类别不同会出现警告但仍然会执行，但在一些面向对象语言中语法更严格，无法传递值

#include <stdio.h>

void myswap(int buf) {
    printf("the buf is %p\n", buf);
}


int main(void) {

    int a = 20;
    char *p = "hello world!";
    char b[10];

    printf("the b is %p\n", b);
    printf("the p is %p\n", p);
    myswap(0x123456789);    // 传入的数值溢出，仍然可以拷贝
    myswap(p);  // 传入类型不匹配，但是大小符合，仍然可以传入

    return 0;
}