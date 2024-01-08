// 结构体定义，成员地址累加偏移

#include <stdio.h>

struct abc {
    char a;
    short b;
    int c;
};

struct my {
    char a;
    int c;
    short b
};

int main(void) { 

    struct abc abc;
    struct my my;
    printf("the size of abc is %lu\n",sizeof(abc));
    printf("the size of my is %lu\n",sizeof(my));

    return 0;
}

// the size of abc is 8
// the size of my  is 12