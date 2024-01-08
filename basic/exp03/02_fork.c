#include <stdio.h>


int main(int argc, char* argv[]){

    int i;
    if (fork() == 0){
        for (i = 1; i < 100; i++)
            printf("This is child process!\n");
    }
    else {
        for (i = 1; i < 100; i++)
            printf("This is parent process!\n");
    }
    
    return 0;
}