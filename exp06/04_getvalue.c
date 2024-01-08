#include <stdio.h>
struct student {
    char *name;
    int age;
};
int main() {

    int num = 0b0010;
    printf("num = %d\n", num);
    num += 1;
    printf("after num += 1,num = %d\n", num);
    num &= 0b1110;
    printf("after num |= 0b1110,num = %d\n", num);
    num |= 0b1110;
    printf("after num += 0b1110,num = %d\n", num);

    int a[5] = {0, 1, 2, 3, 4};
    printf("a[1] = %d\n", a[1]);

    struct student stu;
    printf("the size of student:%lu\n", sizeof(stu));
    char *p = "liang";
    stu.name = p;
    stu.age = 25;
    printf("name:%s, age:%d\n", stu.name, stu.age);

    struct student *stu_ptr = &stu;
    printf("name:%s, age:%d\n", stu_ptr->name, stu_ptr->age);
    printf("name:%s, age:%d\n", *stu_ptr, *((int *)((unsigned long int)stu_ptr+12)));

    return 0;
}