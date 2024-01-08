#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_LEN 128
void main() { 
    FILE *out_file; 
    int count = 1; 
    char buf[BUFFER_LEN];
    out_file = fopen("pipeexample.txt", "w"); 
    if (out_file == NULL) { 
        printf("Error opening pipe."); 
        exit(1); 
    } 
    sprintf(buf, "this is test data for the named pipe example\n"); 
    fwrite(buf, 1, BUFFER_LEN, out_file); fclose(out_file); 
}