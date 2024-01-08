#include <stdio.h>

// 宏定义应用
#define  ABC(x)    #x       // 字符串化
#define  DAY(x)    myday##x // 链接符号

int main() {

    int myday1 = 10;
    int myday2 = 20;
    printf(ABC(ab\n));    //"ab\n"
    printf("the day is %d\n", DAY(1));

    return 0;
}