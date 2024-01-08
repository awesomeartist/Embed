### 一、开发环境
- 开发板：野火指南者
- IDE：keil MDKv5
- 开发方式：标准库开发

### 二、功能实现
功能实现：使用库函数点亮 LED 彩灯，使 RGB 三种颜色小灯依次闪烁，完成芯片 IO 测试

### 三、实现思路
- IO 口初始化
```c
GPIO_InitTypeDef	GPIO_InitStruct;
RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK, ENABLE);
	
GPIO_InitStruct.GPIO_Pin = LED_G_GPIO_PIN;
GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init( LED_RGB_GPIO_PORT, &GPIO_InitStruct);
```
> 使能时钟  
> 设置 IO 为推挽输出模式  
> 设置输出速度  
>  IO 初始化
- LED 点亮
```c
GPIO_ResetBits(LED_RGB_GPIO_PORT, LED_G_GPIO_PIN);
Delay(1000);
GPIO_SetBits(LED_RGB_GPIO_PORT, LED_G_GPIO_PIN);
```
> 置位/复位函数接口实现 IO 高低电平输出
- 关于延时
```c
void Delay(uint32_t Num) {
    for (int i = Num; i > 0; i--) {
        for (int j = 8000; j > 0; j--);
    }
}
```
> 软件延时，不准确且占用较多资源