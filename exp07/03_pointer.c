#include <stdio.h>


int main(void)
{
    float a = 1.2;
    int *p = &a;    // 错误,可用unsigned char 得到9
    printf("the p1 is %x\n", *p);    // 错在 printf

    return 0;
}
//the a is 3f99999a