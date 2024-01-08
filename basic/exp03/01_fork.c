#include <stdio.h>


int main(int argc, char* argv[]) {

    if (fork() == 0) {
        for (int i = 1; i < 3; i++)
            printf("This is child process!\n");
    }
    else {
        for (int i = 1; i < 3; i++)
            printf("This is parent process!\n");
    }
    
    return 0;
}