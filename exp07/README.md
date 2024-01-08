<h2><center>指针概述</center></h2>

> 指针：内存类型资源地址、门牌号的代名词  
> 指针变量：存放指针这个概念的盒子  


C语言编译器对指针概念的两个疑问：

### 一、分配一个装变量的内存需要多大？

在32bit系统中，指针为4个字节

```c
#include <stdio.h>

int main(void) {

    int    *p1;
    char   *p2; 
    printf("the sizeof p1 is %u\n",sizeof p1); 
    printf("the sizeof p2 is %u\n",sizeof p2);

    return 0;
}
// the sizeof p1 is 8
// the sizeof p2 is 8
```

### 二、内存里存放的地址 所指向 内存的读取方法是什么？

`char *p;`    //*p表示这是个指针，char修饰符表示访问地址时取出1byt

指针指向内存空间一定要保证合法

```c
#include <stdio.h>


int main(void) {    
    int    a = 0x12345678
    int    *p1;
    char   *p2; //错误
    printf("the a is %x\nthe a is %x\n", *p1,*p2); 
    return 0;
}
// the a is 12345678
// the a is 78 (小端存储)
```

```c
#include <stdio.h>

int main(void) {

    float a = 1.2;
    int *p = &a;    // 错误,可用 unsigned char 得到9
    printf("the p1 is %x\n",*p);    // 错在printf

    return 0;
}
// the a is 3f99999a
```

---

<h2><center>指针修饰符</center></h2>
### 一、指针修饰符 const

> 常量、只读【不能变】

内存属性：

- 内存操作的大小
- 内存的变化性，可读可写
```c
char    *p;
const char *p;        // 数据为只读模式    "hello world"
char const *p;

char *const p;        // 指针不可变，一般指向为硬件资源    LCD
char *p const;

const char *const p;  // 指针和数据均不可变              ROM
```

```c
#include <stdio.h>

int main() {

    char *p1 = "hello world!\n";
    char buf[] = {"hello world!"};
    char *p2 = buf;

    printf("the one is %c\n", *p1);

    // *p1 = 'a';   // 内存非法修改，段错误
    *p2 = 'a';
    printf("the one is %s\n", p2);  // 输出字符串时传入的是首地址

    return 0;
}
```

### 二、指针修饰符 volatile

> 防止优化指向内存地址，多用于硬件操作

```c
while (*p == 0x10)
    xxx;
```

### 三、指针修饰符 typedef

> 给指针变量定义取别名，便于见名知义

```c
char *name_t;           // name_t是一个指针，指向了一个char类型的内存
typedef char *name_t;   // name_t是一个指针类型名称，指向了一个char类型的内容

name_t abc;
```

---

<h2><center>指针运算符</center></h2>

### 一、指针运算符加减标签操作

> 指针的加法和减法运算，实际上加的是一个单位，单位的大小可以使用sizeof(*p)

```c
int *p;     // p+1 ==p+sizeof(*p)

char *p;    // p+1 ==p+sizeof(*p)


p++;        // 指针改变，指针加1
p--;        // 指针改变，指针减1
```

### 二、指针标签访问操作

> 地址内容的标签访问方式，非线性访问

变量名[n]

n:标签

不同于指针加减运算，该操作在于取出内存里的值

### 三、指针逻辑运算符操作

> 一般多进行是否相等操作，对于大小判断没有太大意义

- 跟一个特殊值进行比较  
`if(p == 0x0);    // 0x0:地址的无效值，结束标志,可用 NULL`

- 指针必须是同类型比较才有意义

<h2><center>多级指针</center></h2>

> 指针变量指向的位置存放的仍然是指针,一般用于描述不同内存空间的关系
> 指针指向存放地址的地址空间

`int **p;`

p[0]    p[1]        ...    p[n]

p[m] == NULL    -->结束了

```c
#include    <stdio.h>


int main(int argc,char **argv) {    
    int i;
    for(i=0;i<argc;i++){
         printf("the argv[%d] is %s\n",i,argv[i]);
        }
    return 0;
}
```

---

<h2><center>数组</center><h2>

### 定义一个空间

1. 大小

2. 读取方式

数据类型    数组名[m]    m的作用域是在申请的时候有用  
`int a[100];`

数组名是一个常量符号，一定不要放到=的左边，也不能加减

```c
char buf[100];
buf = "hello world!";   // 这会发生错误
```

越界

### 空间的赋值

> 按照标签逐一处理

```c
int a[10];  // [0 - 9];
a[0] = xx;
a[1] = yy;
```

程序员这样赋值，工作量较大，可以让编译器进行一些处理，帮助程序员写如上的程序  
===》空间定义时，就告知编译器空间的初始化情况，空间的第一次赋值，初始化操作

`int a[10] = 空间;`

**C语言本身，CPU内部一般不支持空间的拷贝**

```c
int a[10] = {10,20,30}; 
// 等价于
// ===>
a[0] = 10;
a[1] = 20;
a[2] = 30;
a[3] = 0;   // 默认后一位为0，根据需要决定是否让后续的值赋值为0
```

数组空间的初始化和变量的初始化本质不同，尤其在嵌入式的裸机开发中，空间的初始化往往需要库函数的辅助

`char buf[10] = {'a','b','c'};`

> buf当成普通内存来看，没有问题  
> buf当成一个字符串来看，最后应加上一个‘\0’    0

**字符串的重要属性，结尾一定有一个‘\0’**

```c
char buf[] = "abc";         // buf = 4
char buf[10]  = {"abc"};
char buf[10] = "abc";       // 都是将abc逐一赋值给buf
```


"abc"为常量，在内存中存在，`printf("the "abc" is %x","abc");`得到“abc“的地址
```c
char *p = "abc";    // 这个操作将指针p指向常量"abc"的指针
// 因此如下操作只有第一个成功，第二个试图给常量赋值，错误
buf[1] = 'e';
p[1] = 'e';
```

--------------------------------------------------

**另外,如果想要修改字符串**
```c
buf = "hello world!";   // 错误

// 想要第二次赋值需要重新逐一赋值，或
strcpy(buf, "hello world!");        // 存在内存泄露问题
strncpy(buf, "hello world!", 10);    // 限制了内存空间
```

### 字符空间

- ASCII码编码来解码的空间，--->给人看的

- %s    "abc"    'a'    'b'

- \0 作为结束标志

### 非字符空间

数据采集0x00 - 0xff    8bit

开辟一个存储这些数据盒子

```c
char buf[10];           // ---->string，存储字符串

unsigned char buf[10];  // ---->data，存储数据

buf = "abc";

unsigned char *p = sensor_base;
```
只管逐一拷贝，结束在哪里？只能定义个数  
**拷贝三要素**

1. src
2. dest
3. 个数

```c
int buf[10];
int sensor_buf[100];
memcpy(buf, sensor_buf, 10*sizeof(int));

unsigned char buf1[10];
unsigned char sensor_buf[100];  // 00 00 00 23 45 78
strncpy(buf, sensor_buf, 10);   // 仍然失败，遇到 0 时停止拷贝
memcpy(buf, sensor_buf, 10*sizeof(unsigend char));
```

---

<h2><center>指针数组</center></h2>

> 数组中存放的是地址

```c
int a[100];
char *a[100];   // sizeof(a) = 100*4
char **a;
```

两种指针逻辑相似,但注意区分，保存方式不同

### 数组名的保存

```c
int *p1 = a[10]; // 定义一个指针，指向int a[10]的首地址

// 定义一个指针，指向int a[5][6]/int a[2][3][4]的首地址
int b[5][6];
int c[2][3][4];
int (*p2)[6] = b;    // 按行读取，一次读6列
int (*p3)[3][4] = c; // 按面读取，一次读面的大小为3*4
```


<h2><center>结构体字节对齐</center></h2>
一个实例：

```c
#include <stdio.h>

struct abc{
    char a;
    int a;
};

int main(void)
{    
    struct abc myabc;
    printf("the size of myabc is %lu\n", sizeof(myabc));
    return 0;
}

// the size of abc is 8
```

牺牲空间换取时间效率

另一个例子:

```c
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
```

<h2><center>内存分布思想概念</center></h2>

### 一、内存属性

1. 代码和数据的大小
2. 代码和数据放在在哪里

一个例子：

```c
#include <stdio.h>

int main(void) {

    int a;
    printf("the &a is   %p\n",&a);
    printf("the main is %p\n",main);

    return 0;
}
```
### 二、内存分布思想概述

0xFFFF FFFF;                                                         (4G)

---

内核空间                应用程序不许访问

---

栈空间                    局部变量                                    (3G)

---

运行时的堆空间     malloc

---

全局的数据空间    （初始化的 --data，未初始化的 --bss）          RW

只读数据段            "hello world!"                                R，可访问，但修改会发生段错误

代码段                    code                                             R

---

0x0000 0000;

### 三、内存分布之数据段
#### 三个工具
- size
- strings  
- nm
```c
#include <stdio.h>

int b = 10;     // 全局数据空间，已初始化，存放在 data 区域

int fun() {
    static int a = 0x10;    // 全局数据空间，已初始化，存放在 data 区域，但是与外部的 a 有区分
    return a++;
}

int main(void) {
    
    static int a = 10;     // 全局数据空间，未初始化存放在 bss 区域
    unsigned char *p1;

    printf("the size of a is %lu\n", sizeof(a));
    printf("the size of b is %lu\n", sizeof(b));
    printf("the size of p1 is %lu\n", sizeof(p1));
    
    p1 = (unsigned char*)main;
    printf("the &a is   %p\n", &a);     // %p 输出指针变量
    printf("the &b is   %p\n", &b);

    printf("the  *p1 is %d\n", *p1);

    return 0;
}
```
### 四、内存分布之只读空间
**代码段访问修改例子：**
```c
#include <stdio.h>

int fun() {
    static int a = 0x10;
    printf("in fun, the address of a is %p\n", &a);
    return a++;
}

int main(void) {
    
    static int a;
    unsigned char *p1;
    char *p2 = "helao world!";  // 存放在只读空间数据段
    const int b = 0x12345678;

    printf("the size of a is %lu\n", sizeof(a));
    printf("the size of b is %lu\n", sizeof(b));
    printf("the size of p1 is %lu\n", sizeof(p1));

    a = 0x10;
    p1 = (unsigned char*)main;
    fun();
    printf("the main is %p\n", main);
    printf("in main, the &a is   %p\n", &a);     // %p 输出指针变量
    printf("in main, the &b is   %p\n", &b);
    printf("the p2 is %s\n", p2);
    printf("the string address is %p\n", "helao world!");
    p2[3] = 'l';    // 只读空间不可修改，段错误


    printf("the  *p1 is %d\n", *p1);
    *p1 = 0x12;                         // 段错误
    printf("the *p1 is %d\n", *p1);

    return 0;
}
```

### 五、内存分布之堆空间
> 运行时，可以自由自我管理的分配和释放的空间，生存周期由程序员决定

分配：  
    malloc()，一旦成功，返回分配好的地址给我们，只需要接受对这个新地址的读取方法，由程序员灵活把握输入参数只读分配大小，单位是 B
```c
char *p;
p = (char *)malloc(100);
if (p == NULL) {
    error;
}
```

```c
void fun() {
    char *p;
    p = (char *)malloc(100);
    return;
}
```

