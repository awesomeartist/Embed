### 一、开发环境
- 开发板：野火指南者
- IDE：keil MDKv5
- 开发方式：标准库开发

### 二、功能实现
功能介绍：程序用于学习串口的基本使用方法，完成对来自串口调试助手的字符串的接收和发送，发送字符串时，绿色 LED 闪烁

### 三、实现思路
#### 用户文件：
- main.c：调用函数完成初始化和接收发送任务
- uart.c：中断初始化函数 void NVIC_INIT(void) 功能实现；  
        串口初始化函数 void STM_COMInit(void) 功能实现；  
        字符串发送函数 void USART1_SendString(USART_TypeDef *USARTx, char *str)实现；  
        串口中断服务函数 void USART1_IRQHandler(void)功能实现；
- uart.h：函数声明，参数名抽象定义
- led.c：指示灯输出端口配置函数实现
- led.h：端口名抽象定义

#### 库函数文件：
- misc.c：中断驱动配置函数
- stm32f10x_gpio.c：GPIO口驱动配置函数
- stm32f10x_rcc.c：时钟驱动配置函数
- stm32f10x_usart.c：串口驱动配置函数
- stm32f10x_it.c：中断服务函数定义，不一定写在里面
- stm32f10x_xx.h：存放片上外设的初始化结构体，片上外设初始化结构体成员的参数列表，片上外设固件库函数的声明
- stm32f10x.h：片上外设的寄存器映射

- core_cm3.c：内核相关（stdint.h有一些宏定义，如uint8_t等）
- core_cm3.h：内核函数声明与一些结构体定义以及其他宏定义
- system_stm32f10x.c：时钟配置，本程序默认72MHz