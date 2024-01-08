## 一、编译过程

### 0.预处理
对 include 与 define 等预处理指令进行展开（打开 -E 选项 `gcc -E a.i 01_build.c`）

### 1. 编译
编译生成后缀为`.s`的汇编文件（打开 -S 选项 `gcc -S -o a.s 00_hello.c`）

### 2. 汇编
汇编生成后缀为`.o`的二进制文件（打开 -c 选项 `gcc -c -o a.o a.s`）

### 3. 链接
链接多个`.o`文件生成可执行文件（直接使用 -o 选项 `gcc -o build 00_hello.c`）

## 二、C语言编译过程常见错误

### 1. 预处理错误
`#include  "name"  `常为自定头文件  
`#include  <name>`常为系统头文件

错误提示：not find  
解决方法：gcc -I + 头文件目录

### 2. 编译错误

一般为语法错误 ：
- 未添加`;`,括号不匹配，存在中文字符等低级错误
- 逻辑错误

### 3. 链接错误

- 原材料不够，undefine reference to 'func name'  
寻找标签是否实现了，在链接时是否加入一起链接

- 原材料过多，multiple definition of 'func name'  
多次实现了标签，只保留一个标签实现

