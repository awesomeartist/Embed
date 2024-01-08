#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_LEN 128

void main() { 
    FILE *in_file; 
    int count = 1; 
    char buf[BUFFER_LEN]; 
    in_file = fopen("pipeexample.txt", "r"); 
    if (in_file == NULL) { 
        printf("Error in fdopen.\n"); 
        exit(1); 
        } 
    while ((count = fread(buf, 1, BUFFER_LEN, in_file)) > 0) 
    printf("received from pipe: %s\n", buf); 
    fclose(in_file); 
}