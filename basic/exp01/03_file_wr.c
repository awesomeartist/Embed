// 功能：实现文件读写
// 方法：FileBasic2-C语言库函数

#include <stdio.h>

#define LENGTH 100

int main(int argc, char *argv[]) {

  FILE *fd;
  char str[LENGTH];
 
  fd = fopen("hello.txt", "w+");    // 创建并打开文件
  if (fd) {
    fputs("Hello, world!", fd);     // 写入 "Hello world!" 字符串
    fclose(fd);
  }
 
  fd = fopen("hello.txt", "r");
  fgets(str, LENGTH, fd);           // 读取文件内容
  printf("%s\n", str);
  fclose(fd);

return 0;
}
