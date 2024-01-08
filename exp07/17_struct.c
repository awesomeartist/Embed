#include <stdio.h>

struct abc{
    char a;
    short b;
    int c;
};

struct bcd{
    char a;
    int c;
    short b;
};
int main(void) {    
    struct abc myabc;
    struct bcd mybcd;
    printf("the size of myabc is %lu\n", sizeof(myabc));
    printf("the size of mybcd is %lu\n", sizeof(mybcd));
    return 0;
}

// the size of abc is 8
// the size of my  is 12