#include <stdint.h>

int main() {

    int a[10];      // 定义一个指针，指向int a[10]的首地址
    int b[5][6];
    int c[2][3][4];

    int *p1 = a;
    // int *p2 = b;    // 错误  
    int (*p2)[6] = b;    // 按行读取，一次读6列
    int (*p3)[3][4] = c; // 按面读取，一次读面的大小为3*4

    return 0;
}