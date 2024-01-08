// 数据类型的深入理解

#include "stdio.h"

int main(void) {

    char a = -1;            // 定义了一个 char 类型 a 变量并赋值 -1，a = 0b1111 1111
    printf("a = %d\n", a);
    a >>= 8;                // 右移八位，第一位是符号位，右移不改变，仍有 a = 0b1111 1111
    printf("a = %d\n", a);
    unsigned char b = -1;   // 定义了一个无符号 char 类型 b 变量并赋值 -1，b = 0b1111 1111
    printf("b = %d\n", b);  
    b >>= 8;                // 右移八位，无符号位，右移补零，移位后有 a = 0b0000 0000
    printf("b = %d\n", b);

    return 0;
}
/*
output:
a = -1
a = -1
b = 255
b = 0
*/
