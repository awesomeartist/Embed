#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 返回指针类型需要考虑指向空间的合法性(非局部变量)
char* fun(void) {
#if 0
    char buf[] = "hello world!";
    // static char buf[] = "hello world!";   // 局部变量变为静态区
    return buf; // warning: function returns address of local variable [-Wreturn-local-addr]
#elif 0
    static char buf[] = "hello world!";     // 局部变量变为静态区
    return "hello world!";  // 常量存放在常量区（只读区），局部函数销毁仍然存在，但是不实用
#elif 1
    char* s = (char*)malloc(100);// 堆区，需要在使用完后释放
    strcpy(s, "hello world!");
    return s;
#endif
}

int main(void)
{
    char* p;
    p = fun();
    printf("the p is %s\n",p);
    free(p);

    return 0;
}
