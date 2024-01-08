#include <stdio.h>

int fun1(int p,char str);
int fun2(int p ,char str);

int main(void) {  

    int day = 0;
    int (*fun[2])(int, char );  // 定义函数指针数组保存函数入口地址
    fun[0] = fun1;
    fun[1] = fun2;

    fun[day](0,'a');

    return 0;
}

int fun1(int p, char str) {
    printf("This is Monday!\n");
}

int fun2(int p, char str) {
    printf("This is Tuesday!\n");
}