### 一、开发环境
- 开发板：野火指南者
- IDE：keil MDKv5
- 开发方式：寄存器开发

### 二、功能实现
不依赖官方固件库，自己实现部分固件库的功能，点亮 LED

### 三、实现思路
- stm32f10x_gpio.h管脚映射，包含管脚号、管脚模式、管脚输出速度等
- stm32f10x_gpio.c管脚配置函数实现，包含管脚初始化函数、置位函数、复位函数，时钟初始化仍直接对寄存器进行配置
- stm32f10x.h寄存器地址映射，包括外设基地址PERIPH_BASE、APB1_PERIPH_BASE、APB2_PERIPH_BASE、AHB_PERIPH_BASE等