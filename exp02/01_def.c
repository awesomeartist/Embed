#include <stdio.h>

void fun() {
    int a;
    printf("function: %s,\nfilename: %s,\nline: %d\n", __FUNCTION__, __FILE__, __LINE__);
}

int main() {
    
// 作用域限制
#ifdef    ABC    
    printf("====%s====\n", __FILE__);
#endif
    fun();
    printf("hello world!\n");

    return 0;
}