#include <stdio.h>

int main(void) {

    int a = 10;
    int res;
    res = ((a == 10) || printf("========\n"));
    printf("the res is %d\n",res);

    printf("a = %d, a > 10: %d\n", a, a>10);
    printf("a = %d, a < 11: %d\n", a, a<11);
    printf("a = %d, a >= 10: %d\n", a, a>=10);
    printf("a = %d, a <= 11: %d\n", a, a<=11);
    printf("a = %d, !a: %d\n", a, !0);
    a > 9 ? printf("a > 9\n") : printf("a < 9\n");

    return 0;
}

// the res is 1
// 取a!=10时
// =======
// the res is 1