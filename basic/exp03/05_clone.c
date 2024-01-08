#define _GNU_SOURCE   /*注意摆放位置*/         
#include <sched.h>   /*注意摆放位置*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int variable, fd; 
int do_something() { 
    variable = 42; 
    close(fd); 
    _exit(0); 
    }
int main(int argc, char *argv[]) { 
    void **child_stack; 
    char tempch; 
    variable = 9; 

    fd = open("test.file", O_RDONLY); 
    child_stack = (void **) malloc(16384); 
    printf("The variable was %d\n", variable); 
    clone(do_something, child_stack, CLONE_VM | CLONE_FILES, NULL); 
    sleep(1); /* 延时以便子进程完成关闭文件操作、修改变量 */ 
    printf("The variable is now %d\n", variable);

    if (read(fd, &tempch, 1) < 1) { 
        perror("File Read Error"); 
        exit(1); 
        }

    printf("We could read from the file\n"); 
    return 0; 
}