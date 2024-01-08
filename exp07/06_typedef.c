#include <stdio.h>

int main() {

    // char *name_t;           // name_t是一个指针，指向了一个char类型的内存
    typedef char* name_t;   // name_t是一个指针类型名称，指向了一个char类型的内容

    name_t abc;

    return 0;
}