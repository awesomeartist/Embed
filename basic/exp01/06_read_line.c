#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<errno.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {

    char buf[MAX_LINE];  // 缓冲区
    FILE *fp;            // 文件指针
    int len;             // 行字符个数

    fp = fopen("log.txt", "r");
    if(fp == NULL) {
        perror("fail to read!");
        exit (1) ;
    }
    
    while((fgets(buf, MAX_LINE, fp)) != NULL) {
        len = strlen(buf);
        buf[len-1] = '\0';  // 去掉换行符
        printf("%s line length = %d \n", buf, len - 1);
    }

    return 0;
}