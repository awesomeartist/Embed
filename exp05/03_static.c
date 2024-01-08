#include <stdio.h>

int func() {  

    int a; 
    // static int a;    // 修饰函数内局部变量
}

// 函数修饰符
// int func();
// static int func();

int main(void) {

    static int a; // 全局变量修饰
    printf("the main is %d\n",main);

    return 0;
}
// the main is 1499459913