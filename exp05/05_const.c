#include <stdio.h>

int main() {

    const int a = 100;
    printf("a = %d\n", a);
    // a = 200;    // 不能进行
    int *p = (int*)&a;
    *p = 200;
    printf("a = %d\n", a);
    
    return 0;
}