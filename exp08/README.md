### 一、函数概述

> 一堆代码的集合，用一个标签去描述它  
> 目的：复用化

标签——函数名

**相对于数组，函数具有三要素**

`int *p;`

`int a[100];`

1. 函数名    （地址）
2. 输入参数
3. 返回值

在定义函数时，必须将三要素告知编译器。  
```c
int fun(int a, int b, char c) {
    xxx;
}
```
**如何用指针保存函数？**

```c
char *p;

char (*p)[10];

int (*p)(int a,int b,char c);
```

定义函数，调用函数

```c
int fun(int a,char b) {
    xxx;
}

int main() {

    fun(10,2);

}
```


> 标签不同访问方式不同，中括号表示访问内存数据，小括号表示调用函数，PC指针指向代码段



**示例一：**

```c
#include <stdio.h>

int main() {

    int (*myshow)(const char*,...);
    printf("hello world!");
    myshow = printf;
    // myshow = (int(*)(const char*,...))0x8048320; // printf函数地址
    myshow("==========\n");

    return 0;
}
// hello world!
// ===========
```
**示例二：**
```c
#include <stdio.h>

int fun1(int p,char str);
int fun2(int p ,char str);

int main(void) {  

    int day = 0;
    int (*fun[2])(int, char );  // 定义函数指针数组保存函数入口地址
    fun[0] = fun1;
    fun[1] = fun2;

    fun[day](0,'a');

    return 0;
}

int fun1(int p, char str) {
    printf("This is Monday!\n");
}

int fun2(int p, char str) {
    printf("This is Tuesday!\n");
}
```
### 二、函数实参和形参的概念
调用者：  
    `函数名（要传入的参数） // 实参`  
被调者：  
    函数的具体实现  
```c
    函数的返回值 函数名 （接收的数据） { // 形参  
        xxx;
    }
```
实参 传递给 形参  
传递的形式：拷贝  

**实例**
```c
// 实参传递给实参的方式：拷贝（不论是值传递还是地址传递，本质都是拷贝）
// 本质是对内存的拷贝，类别不同会出现警告但仍然会执行，但在一些面向对象语言中语法更严格，无法传递值

#include <stdio.h>

void myswap(int buf) {
    printf("the buf is %p\n", buf);
}


int main(void) {

    int a = 20;
    char *p = "hello world!";
    char b[10];

    printf("the b is %p\n", b);
    printf("the p is %p\n", p);
    myswap(0x123456789);    // 传入的数值溢出，仍然可以拷贝
    myswap(p);  // 传入类型不匹配，但是大小符合，仍然可以传入

    return 0;
}
```
### 三、值传递与地址传递
```c
// 函数值传递与地址传递
// 值传递：上层，调用者保护自己的空间值不被下层，子函数修改的赋值方式
// 地址传递：上层，调用者 让下层，子函数修改自己空间值的方式

#include <stdio.h>

void swap(int* p1, int *p2) {
    int c;
    c = *p1;
    *p1 = *p2;
    *p2 = c;
}

void swap1(int a, int b) {
    int c;
    c = a;
    a = b;
    b = c;
}

int main(void)
{
    int a = 20;
    int b = 30;
    int c;

    // c = a;
    // a = b;
    // b = c;

    printf("the a is %d,the b is %d\n", a, b);

    printf("after swap\n");
    swap(&a,&b);
    printf("the a is %d,the b is %d\n", a, b);

    printf("after swap1\n");
    swap1(a,b);
    printf("the a is %d,the b is %d\n", a, b);

    return 0;
}
```

### 四、连续空间地址传递
1. 数组  
数组名--标签  
实参：  
int abc[10];  
fun(abc[10]);
2. 结构体  
结构体变量  
```c
#include <stdio.h>

#define M 3
#define N 4

struct abc {
    int a;
    int b;
    int c;
};

void fun1_1(int array[][4], int m, int n) { // 形参声明为二维数组
    printf("the address is %p\n", array);
    int max = array[0][0];
	for (int i = 0; i < m; i ++) {
		for (int j = 0; j < n; j ++) {
			if (max < array[i][j]) 
                max = array[i][j]; 
		}
	}
	printf("max in array is %d\n", max);
}
void fun1_2(int *array, int m, int n) {     // 形参声明为一级指针
    printf("the address is %p\n", array);
    int max = array[0];
	for (int i = 0; i < m * n; i ++) {
		if(max < array[i]) 
            max = array[i];
	}
    printf("max in array is %d\n", max);
}
void fun1_3(int **array, int m, int n) {    // 形参声明为二级指针
    printf("the address is %p\n", array);
    int max = array[0][0];
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if(max < array[i][j]) 
                max = array[i][j];
		}
	}
    printf("max in array is %d\n", max);
}

void fun2(struct abc myabc) {
    printf("the address is %p\n", &myabc);
}

void fun3(struct abc *myabc) {
    printf("the address is %p\n", myabc);
}

int main()
{
    int a[M][N] = {{1, 2, 3, 4}, {2, 3, 4, 5}, {3, 4, 5, 6}};
    struct abc myabc;

    int *p1 = a[0]; // 定义指针用于储存二维数组第一行的首地址，也就是把二维数组当作一维数组
    int *p2[M];     // 定义指针数组用于储存二维数组每行的首地址
    p2[0] = &a[0][0];
    p2[1] = &a[1][0];
    p2[2] = &a[2][0];
    
    fun1_1(a, M, N);
    fun1_2(p1, M, N);
    fun1_3(p2, M, N);
    fun2(myabc);
    fun3(&myabc);


    return 0;
}
```
### 五、连续空间只读性
```c
const char *p;  // 只读

char *p;        // 可读可写

void fun(const char*p); // p指向空间只读

void fun(char *p);       // p指向空间可写
```

**实例**
```c
#include <stdio.h>

void fun1(char *p) {
    p[1] = '2';
}

void fun2(const char *p) {
    // p[1] = 'e'; // 错误编译不通过
    char *p1 = p;
    p1[1] = 'e';
}

int main()
{
    char buf[] = "hello world!";
    fun1(buf);
    printf("buf = %s\n", buf);
    fun2(buf);
    printf("buf = %s\n", buf);

    return 0;
}
```
### 六、字符空间和非字符空间访问操作
**地址传递的作用**  
1. 修改 int* char*  
2. 空间传递  
    - 子函数查看空间里的情况    const
    - 子函数反向修改上层空间里的内容  

> 空间：空间首地址、结束标志  
> 字符空间和非字符空间的处理方式不同，需要根据实际选择适合的数据处理方法（注意传入的指针类型）

**字符空间**
```c
void fun(char *p) {
// 首先进行错误判断

// 字符操作
while(char *p!=NULL) {  // 通过字符结束标识符判断访问空间
    xxx；
    }
}
```
两个字符串库函数 
- strlen
- strcpy

**非字符空间**

```c
void fun(unsigned char *p, int len) {
// 首先进行错误判断

// 非字符操作
while(i<len) {  // 通过len限制访问空间
    xxx；
    }
}
```

`void memory(void *)   // 非字符空间拷贝会存在较多类型数据，使用void声明定义函数`

```c
int fun(void *buf, int len) {
    unsigned char *tem = (unsigned char*)buf;
    tem[i]=;
    i++;
    len;

}
```
### 七、函数返回

