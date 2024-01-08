<h1><center>C 语言基础 - 嵌入式</center></h2>

## 面试题
1. 用预处理指令 #define 声明一个常数，用以表明 1 年中有多少秒（忽略润年问题）  
```c
// #define 宏名 宏体
// 宏名：大写字母表示
#define SECOND_OF_YEAR 365*24*3600      // 表达式常量，在运行前已经完成，不需要考虑乘法效率问题
#define SECOND_OF_YEAR (365*24*3600)UL  // 需要保护常数不溢出
```
2. 用变量 a 给出下面定义
```c
// 一个整型数（A integer）
int a;

// 一个指向整型的指针（A pointer to integer） 
int *a;

// 一个指向指针的指针，它指向的指针指向一个整数（A pointer to a pointer to an integer) 
int **a;

// 一个有10个整型数的数组（A array of 10 integers)
int a[10];

// 一个有10个整型指针的数组，该指针是指向整型数的（An array of 10 pointers to integers）
int *a[10];

// 一个指向有10个整型数数组指针 （A pointer to an array of 10 integers）
// int [10]*a;
int (*a)[10];

// 一个指向函数的指针，该函数有一个整型参数并返回一个整数
// A pointer to a function that takes an integer as an argument and returns a integer
// int fun(int) *a;
int (*a)(int );

// 一个有10个指针的数组，该指针指向一个函数，该函数有一个整型参数并返回一个整型数
// An array of 10 pointers to functions that take an integer argument and return an integer
int (*a[10])(int);
```

3. 修饰符的作用
- 关键字 static 的作用是什么？
    - 修饰局部变量  
    默认局部变量在栈空间存在，生存期比较短  
    局部静态化，局部变量 在静态数据段保存
    - 修饰全局变量  
    防止重名，限制变量仅本文件内生效
    - 修饰全局函数  
    防止重名，限制函数仅本文件内生效

- 关键字 const 有什么含义？  
C：只读，建议性，不具备强制性 （!= 常量）  
C++：常量

- 关键字 volatile 有什么含义？并给出三个不同例子。  
防止 C 语言编译器优化。  
它修饰的变量，该变量的修改可能通过第三方修改

4. 嵌入式系统总是要用户对变量或寄存器进行位操作。给定一个整型变量a,写两段代码，第一段设置a 的 bit3,第二个清除 a 的bit3。在以上操作中，要保持其他位不变。
```c
unsigned int a;
a |= (0x1<<3);  // 置位

a &= ~(0x1<<3); // 清零
```
5. 在某工程中，要求设置一绝对地址为 0x67a9的整型变量的值为 0xaa66。编译器是一个存粹的ANSI编译器。写代码完成这一任务。
```c
int *p = (int *)0x67a9;
p[0] = 0xaa66;

*((int *)0x67a9) = 0xaa66;  // 简洁

((void(*)(void))0x67a9)();  // PC 指向0x67a9执行程序
``` 

6. 写一个“标准宏”MIN，这个宏输入两个参数并返回较小的一个
```c
#define MIN(A, B) (A<B?)?A:B
```

> 标识#define在宏中应用的基本知识。这是很重要的，因为直到嵌入(inline)操作符变为标准C的一部分，
宏是方便产生嵌入代码的唯一方法。对于嵌入式系统来说，为了能达到要求的性能，嵌入代码经常是必须的方法。
三重条件操作符的知识。这个操作符存在C语言中的原因是它使得编译器能产生比if-then-else更优化的代码
懂得在宏中小心地把参数用括号括起来

7. 预处理器标识#error的目的是什么？
```c
#空指令，无任何效果
#include    包含一个源代码文件
#define     定义宏
#undef      取消已定义的宏
#if         如果给定条件为真，则编译下面代码
#ifdef      如果宏已经定义，则编译下面代码
#ifndef     如果宏没有定义，则编译下面代码
#elif       如果前面的#if给定条件不为真，当前条件为真，则编译下面代码
#endif      结束一个#if……#else条件编译块
#error      停止编译并显示错误信息
```
```c
/*
当程序比较大时，往往有些宏定义是在外部指定的（如makefile），或是在系统头文件中指定的，
当你不太确定当前是否定义了 XXX 时，就可以改成如下这样进行编译：
*/
#ifdef XXX
...
#error "XXX has been defined"

#else

#endif

//这样,如果编译时出现错误,输出了XXX has been defined,表明宏XXX已经被定义了

```
```c
#ifndef __ADC_H
#define __ADC_H	
...
....
....
#endif 
```
8. 嵌入式系统中经常要用到无限循环，你怎么用C写死循环呢？
```c
while(1) {
	......
}

for(;;) {
	......
}


loop:

......

goto Loop;


do {
	......
	
}while(1);

```
9. 中断是嵌入式系统中重要的组成部分，这导致了很多编译开发商提供一种扩展—让标准C支持中断。具代表事实是，产生了一个新的关键字__interrupt。下面的代码就使用了__interrupt关键字去定义了一个中断服务子程序(ISR)，请评论一下这段代码的。
```c
__interrupt double compute_area (double radius) {

    double area = PI * radius * radius;
    printf(" Area = %f", area);

    return area;

}
```
> ①ISR 不能返回一个值。  
②ISR 不能传递参数。  
③在许多的处理器/编译器中，浮点一般都是不可重入的。有些处理器/编译器需要让额处的寄存器入栈，有些处理器编译器就是不允许在ISR中做浮点运算。此外，ISR应该是短而有效率的，在ISR中做浮点运算是不明智的；  
④与第三点一脉相承，printf()经常有重入和性能上的问题。

10. 下面的代码输出是什么，为什么？
```c
void foo(void)

{

unsigned int a = 6;

int b = -20;

(a+b > 6) puts("> 6") : puts("<= 6");

}
```
> 当表达式中存在有符号类型和无符号类型时所有的操作数都自动转换为无符号类型。 因此-20变成了一个非常大的正整数，所以该表达式计算出的结果大于6。这一点对于应当频繁用到无符号数据类型的嵌入式系统来说是丰常重要的。

11. 评价下面的代码片断：
```c
unsigned int zero = 0;

unsigned int compzero = 0xFFFF;
```
> 对于一个int型不是16位的处理器为说，上面的代码是不正确的。应编写如下：
unsigned int compzero = ~0;(提高兼容性，避免在非32位处理器下出错)
是否懂得处理器字长的重要性

12. Typedef 在C语言中频繁用以声明一个已经存在的数据类型的同义字。也可以用预处理器做类似的事。例如，思考一下下面的例子：
```c
#define dPS struct s *
typedef struct s * tPS;
```
以上两种情况的意图都是要定义dPS 和 tPS 作为一个指向结构s指针。哪种方法更好呢？（如果有的话）为什么？

答案是：typedef更好。思考下面的例子：
> dPS p1,p2;  
tPS p3,p4;  
第一个扩展为  
struct s * p1, p2;  
上面的代码定义p1为一个指向结构的指，p2为一个实际的结构，这也许不是你想要的。第二个例子正确地定义了p3 和p4 两个指针。

13. C语言同意一些令人震惊的结构,下面的结构是合法的吗，如果是它做些什么？
```c
int a = 5, b = 7, c;
c = a+++b;
```
> 上面的例子是完全合乎语法的。问题是编译器如何处理它？水平不高的编译作者实际上会争论这个问题，根据最处理原则，编译器应当能处理尽可能所有合法的用法。因此，上面的代码被处理成：  
c = a++ + b;  
因此, 这段代码持行后a = 6, b = 7, c = 12。