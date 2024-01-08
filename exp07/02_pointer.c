#include <stdio.h>


int main(void){    
    int    a = 0x12345678;
    int    *p1 = &a;
    char   *p2 = &a; // 错误
    printf("the a is %x\nthe a is %x\n", *p1, *p2); 
    return 0;
}
//the a is 12345678
//the a is 78 (小端存储)