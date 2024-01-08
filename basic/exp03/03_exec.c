#include <stdio.h>


int main(int argc, char* argv[]){

    int i;
    if (fork() == 0){
        printf("This is child process!\n");
    }
    else {
        printf("This is parent process!\n");
    }
    
    return 0;
}