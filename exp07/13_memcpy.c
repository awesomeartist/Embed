#include <stdio.h>
#include <stdlib.h>

int main() {

/*  
    char buf[10];           // ---->string，存储字符串
    unsigned char buf[10];  // ---->data，存储数据
    buf = "abc";
    unsigned char *p = sensor_base; 
*/

    int buf[10];
    int sensor_buf[100];
    memcpy(buf, sensor_buf, 10*sizeof(int));

    unsigned char buf1[10];
    unsigned char sensor_buf[100];  // 00 00 00 23 45 78
    strncpy(buf, sensor_buf, 10);   // 仍然失败，遇到 0 时停止拷贝
    memcpy(buf, sensor_buf, 10*sizeof(unsigned char));

    return 0;
}