#include <stdio.h>

int main() {

    char *p1 = "hello world!\n";
    // const char *p1 = "hello world!\n";   // 标准写法，字符串串常量不可修改
    char buf[] = {"hello world!"};
    char *p2 = buf;

    printf("the one is %c\n", *p1);

    // *p1 = 'a';   // 段错误
    *p2 = 'a';
    printf("the one is %s\n", p2);  // 输出字符串时传入的是首地址

    return 0;
}