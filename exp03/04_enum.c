#include <stdio.h>

// enum 枚举类型看作是被命名的整数集合
enum week {     // week 代名词可去掉
    Monday = 0,
    Tuesday = 1,
    Wednesday = 2,
    Thursday = 3,
    Friday,
    Saturday,
    Sunday
};

// 同样有宏定义可以实现，用来替换枚举类型
#define Monday 0

int main() {

    printf("the %d \n", Saturday);
    enum week enum1 = 800;          // 仍然可以赋值枚举类型之外的值，并非强制符号
    printf("the size of enum1 is:%lu\n", sizeof(enum1));
    printf("enum1 = %d\n", enum1); 

    return 0;
}
/*
output：
the 5 
the size of enum1 is:4
enum1 = 800
*/