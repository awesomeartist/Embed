#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    
    char buf[] = "abc";         // buf = 4
    // char buf[10]  = {"abc"};
    // char buf[10] = "abc";       // 都是将abc逐一赋值给buf
    printf("the buf is %s\n", buf);


    char *p = "abc";    // 这个操作将指针p指向常量"abc"的指针
    // 因此如下操作只有第一个成功，第二个试图给常量赋值，错误
    buf[1] = 'e';
    // p[1] = 'e';
    printf("the buf is %s\n", buf);

    // buf = "hello world!";   // 错误
    // 想要第二次赋值需要重新逐一赋值，或
    strcpy(buf, "hello world!");        // 存在内存泄露问题
    printf("the buf is %s\n", buf);
    strncpy(buf, "hello world!", 10);    // 限制了内存空间
    printf("the buf is %s\n", buf);

    return 0;

}