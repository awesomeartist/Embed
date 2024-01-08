

**关键字：编译器预先定义了一定意义的字符串**

<h2><center> 特殊关键字</center></h2>

### 一、关键字 sizeof
> sizeof 是一个关键字，而不是一个函数，由编译器实现，作用是获取变量空间容量

### 二、关键字 return
> 返回的概念

---

<h2><center> 基本数据类型</center></h2>

### 一、char 数据类型

- C语言操作对象：资源/内存（内存类型资源，LCD缓存，LED灯
- C语言使用关键字对这些资源限制管理访问
- 硬件芯片操作的最小单位：bit    0/1
- 软件操作的最小单位：8bit == 1B
- char 被认为是硬件处理的最小单位,char能代表的最大数值只有256（ASC II码）

### 二、int 数据类型

- 大小：根据系统编译器得到，不确定

- 编译器最优的处理大小：系统一个周期，所能接受的最大处理单位，int
32bit        4B        int  
16bit        2B        int



整型常量
```c
char a = 300;   // 300l        300L

int a = 66535;  // 2B       65535;
```
进制表示

|十进制(decimal)|二进制(binary)|八进制(otal number)|十六进制(hexadecimal)|
|------------|-----------|----------------|-----------------|
|10|0b1010|012|0x0a|
|不需要作说明|常数前加0b/0B|常数前加0|常数前加0x|

### 三、特殊长度的限制符 short/long

- short：一般都会使用int，除非一定要16位
- long：可扩充的修饰符，long   32位,long long 64位

### 四、signed/unsigned 数据类型修饰符

- 无符号：数据（数据采集）
- 有符号：数字（一般只有当我们进行数学运算时使用）

内存空间最高位是符号位还是数据

```c
#include "stdio.h"

int main(void) {
    char a = -1;
    printf("a = %d\n", a);
    a>>=8;
    printf("a = %d\n", a);
    unsigned char b = -1;
    printf("b = %d\n", b);
    b>>=8;
    printf("b = %d\n", b);

    return 0;
}
//ouput:
//a = -1
//a = -1
//b = 255
//b = 0
```

### 五、float/double 数据类型

> 在内存中表示方式与整型有区别，另外在不同计算机原理的计算机中表示方式也不同

- 1.0/1.1    double类型
- 1.0f          float类型，节省空间

### 六、void特殊类型

- `void a;` a不能当成变量使用，仅作为占位符，常用作用为避免编译器警告  
- 一般声明定义变量未使用时会有警告，可用`((void) a)；`，避免编译器警告  
- 一些项目为保证质量，打开-Werro选项，将warming当作错误

---
<h2><center>自定义数据类型</center></h2>
### 一、struct 自定义数据类型

```c
struct myabc {
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
};


struct myabc mybuf;
```

> 内部元素顺序与存储位置有关
> 顺序有要求

### 二、union自定义数据类型

```c
union myabc {
    char a;
    int  b;
};

union myabc abc;
```

> 共用体内部成员共用首地址，修改某一成员其他成员也会改变，常作为技巧性用法
> 这并不是一种数据类型

### 三、enum自定义数据类型

```c
enum week {
    Monday = 0,Tuesday = 1,Wensday = 2,
    Thursday,Friday,Saturday,Sunday
};
```

> 枚举数据 enumerate  
> 枚举一般作为标识符使用，程序上作用不强  
> 占用空间为int字节大小

### 四.typedef数据类型别名

```c
int a;            // a是一个int 类型的变量
typedef int a;    // a是一个int 类型的外号

a mysize;

// 一般a的命名形式为xxx_a，便于识别该数据类型
```


