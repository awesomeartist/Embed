<h2><center>类型修饰符</center></h2>

> 对内存资源存放位置的限定  
> 资源属性中位置的限定

### 一、auto 类型修饰符

> 自动分配存放位置，默认为可读可写状态  
> 在 {} 中一般为栈空间中
```c
auto int a;

auto long  b;
```
### 二、register 类型修饰符

- 限制变量定义在寄存器上的修饰符  
- 定义一些快速访问的变量  
- 编译器会尽量地安排CPU的寄存器区存放这个a，如果寄存器不足时，a还是存放在存储器中  
- 取地址 & 这个符号对register不起作用

```c
#include <stdio.h>

int main(void) {
    register int a;
    a = 0x10;
    //printf("the a is %d", a);
    printf("the a is %d", &a);

    return 0;
}
// the a is 16
// error
```

### 三、static 类型修饰符

> 静态

应用场景：修饰三种数据

1. 函数内的局部变量

```c
int func() {
    int a; 
    static int a; // 限制为函数内局部变量
}
```

2. 函数外的局部变量

```c
int a;
static int a; // 全局变量修饰
int func()
{
    //
}
```

3. 函数的修饰符

```c
#include <stdio.h>

int func(); 
static int func();  // 修饰函数

int main(void)
{
    printf("the main is %d\n",main);

    return 0;
}
// the main is 1499459913
```
### 四、extern 类型修饰符


### 五、const 类型修饰符

> 常量的定义
> 只读的变量
> 不能进行显式的修改

```c
#include <stdio.h>

int main() {

    const int a = 100;
    printf("a = %d\n", a);
    // a = 200;    // 不能进行
    int *p = (int*)&a;
    *p = 200;
    printf("a = %d\n", a);
    
    return 0;
}
```

### 五.volatile 类型修饰符

> 告知编译器编译方法的关键字，不优化编译  
> 修饰变量的值的修改，不仅仅可以通过软件，也可以通过其他方式（硬件外部的用户）

```c
int a = 100;

while(a == 100);

mylcd();
```

Assemble

```unix-assembly
f1:    LDR R0,[a];[a]为a的地址
f2:    CMP R0,#100
f3:    JMP f1
f4:    mylcd();
```

