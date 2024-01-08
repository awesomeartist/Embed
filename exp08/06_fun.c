#include <stdio.h>

void fun1(char *p) {
    p[1] = '2';
}

void fun2(const char *p) {
    // p[1] = 'e'; // 错误编译不通过
    char *p1 = p;
    p1[1] = 'e';
}

int main()
{
    char buf[] = "hello world!";
    fun1(buf);
    printf("buf = %s\n", buf);
    fun2(buf);
    printf("buf = %s\n", buf);

    return 0;
}