#include <stdio.h>

int* fun1(void);    // 返回指针类型修改指针

void fun2(int **p);//输入二级指针**p，在子函数中修改指针（输入*p表示修改指针指向的内容）

int main(void)
{
    int *p;


    p = fun1();
    fun2(&p);

    return 0;
}