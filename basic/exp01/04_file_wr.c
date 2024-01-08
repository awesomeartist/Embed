// 功能：实现文件读写
// 方法：FileBasic2-API 函数

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 100

int main(int argc, char *argv[]) {

    int len;
    int fd;
    char str[LENGTH]; 

    fd = open("hello2.txt", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);   // 创建并打开文件
    if (fd) {
        write(fd, "Hello, world!", strlen("hello, world!"));        // 写入Hello,world字符串
        close(fd);
    }

    fd = open("hello2.txt", O_RDWR);
    len = read(fd, str, LENGTH);        // 读取文件内容
    str[len] = '\0';
    printf("%s\n", str);
    close(fd);

    return 0;

};
