// 函数值传递与地址传递
// 值传递：上层，调用者保护自己的空间值不被下层，子函数修改的赋值方式
// 地址传递：上层，调用者 让下层，子函数修改自己空间值的方式

#include <stdio.h>

void swap(int* p1, int *p2) {
    int c;
    c = *p1;
    *p1 = *p2;
    *p2 = c;
}

void swap1(int a, int b) {
    int c;
    c = a;
    a = b;
    b = c;
}

int main(void)
{
    int a = 20;
    int b = 30;
    int c;

    // c = a;
    // a = b;
    // b = c;

    printf("the a is %d,the b is %d\n", a, b);

    printf("after swap\n");
    swap(&a,&b);
    printf("the a is %d,the b is %d\n", a, b);

    printf("after swap1\n");
    swap1(a,b);
    printf("the a is %d,the b is %d\n", a, b);

    return 0;
}