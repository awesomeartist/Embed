### 一、包含头文件，自定义宏
```c
#include  // 包含头文件
#define   // 宏    替换，不进行语法检查
​#define   //宏    宏名    加括号比较安全
​#define    ABC    (5+3)
​printf("the %d\n", ABC*5);
​#define    ABC(x)    (5+(x))
```

### 二、条件编译
```c
#include <stdio.h>

int main() {
    //作用域限制
#ifdef ABC    
    printf("====%s====", __FILE__);
#endif
    printf("hello world!");
return 0;
}
//output:hello world!
//加入#define ABC 或则编译时加入-D选项：gcc -DABC -o output_name filename.c
//output:====filename====
//         hello world!
```

可以通过定义宏名ABC（不推荐，一般工程存在多个文件，另外尽可能不对已完成的代码进行修改），或者在编译时加入`-D`选项，`-D`后边直接跟着宏名不需要添加空格  
一般用于控制版本切换，debug版本或者release版本

### 三、预定义宏(系统定义宏，平台无关)

`__FUNCTION__`    ：函数名  
`__LINE__`            ：行号  
`__FILE__`            ：文件名

```c
#include <stdio.h>

int fun() {

    int a;
    printf("the %s,%s,%d\n",__FUNCTION__,__FILE__,__LINE__);

    return 0;
}

int main() {

    fun();

    return 0;
}

// output:the fun,filename.c,7
// 查看当前所在函数名，当前文件名，以及当前行号
```

### 四、宏展开下的#、##

> 内核、驱动中用，日常不常用

\#    字符串化

\##    链接符号

`#define    ABC(x)    #x`

`#define    ABC(x)    day##x`

字符串化

```c
#include <stdio.h>

#define  ABC(x)    #x

int main() {

    printf(ABC(ab\n));    //"ab\n"

    return 0;
}
//output:ab
```

利用后缀作一些技巧性的输出

```c
#include <stdio.h>

#define  ABC(x)    #x
#define  DAY(x)    myday##x
int main()
{
    int myday1 = 10;
    int myday2 = 20;
    printf(ABC(ab\n));    //"ab\n"
    print("the day is %d\n", DAY(1));

    return 0;
}
// output:ab
// the day is 10
```

