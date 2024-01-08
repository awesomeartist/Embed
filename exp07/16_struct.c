#include <stdio.h>

struct abc{
    char a;
    int b;
};

int main(void)
{    
    struct abc myabc;
    printf("the size of abc is %lu\n",sizeof(myabc));
    return 0;
}

// the size of abc is 8