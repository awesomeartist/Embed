#include <stdio.h>

char fun1(void) {    // char 决定返回数据时接收数据类型，返回值和函数左边接收变量类型都无法决定
    int a = 0x1234;
    int *p = &a;

    return a;       // 只能返回基本数据类型和指针类型（结构体类型从语法上可以，但是不推荐，实质上还是连续空间类型），指针作为连续空间唯一返回方式
}
int fun2(void);         // 返回整型

int main(void)
{
    int ret;

    ret = fun1();

    printf("the ret is %x\n", ret);

    return 0;
}