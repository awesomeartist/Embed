#include <stdio.h>

int main() {

    volatile char *p;   // 假设指向硬件资源地址
    char val;
    *p = val;
    // 前面给 *p 指向的地址的值赋初值，但是后序由硬件修改
    // 这里为了防止编译器优化把 *p 当成常量优化使用关键字 volatile 修饰
    while (*p == 0x10) {
        // xxxx;
    }

    return 0;
}