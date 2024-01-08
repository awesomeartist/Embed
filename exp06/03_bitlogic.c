#include <stdio.h>

void swap(int* a,int* b);

int main(void) {

    int num1 = 0b00010000, num2 = 0b11111010;
    printf("num1 = %d, num2 = %d\n", num1, num2);
    printf("num1<<2 = %d\n", num1<<2);
    printf("num2>>2 = %d\n", num2>>2);
    printf("num1&num2 = %d\n", num1&num2);
    printf("num1|num2 = %d\n", num1|num2);
    swap(&num1, &num2);
    printf("num1 = %d, num2 = %d\n", num1, num2);
    printf("~num1 = %d\n", ~num1);

    return 0;
}

void swap(int* a,int* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}