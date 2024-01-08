// 功能：测试 Linux 下 GCC 编译工具

#include <stdio.h>

int main(int argc, char *argv[]){

    int i, sum = 0;
    for (i = 1; i<=100; i++)
	    sum += i;
    printf("\n1+2+3+...+99+100 = %d\n", sum);

    return 0;

}
