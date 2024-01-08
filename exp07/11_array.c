#include <stdio.h>

int main() {

    int a[10] = {10, 20, 30};
    // a[0] = 10;
    // a[1] = 20;
    // a[2] = 30;
    // 1[3] = 0;    // 默认后一位为0，根据需要决定是否让后续的值赋值为0

    for (int i = 0; i < 10; i++) {
        printf("the a[%d] is %d\n", i, a[i]);
    }

    return 0;
}