### 一、开发环境
- 开发板：野火指南者
- IDE：keil MDKv5
- 开发方式：标准库开发

### 二、功能实现
配置外部中断获取 KEY1 对应 IO 状态，RGB 颜色切换

### 三、实现思路
- IO 初始化
```C
// LED IO 初始化
void LED_GPIO_Config(void) {
    GPIO_InitTypeDef	GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(LED_G_GPIO_CLK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = LED_G_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init( LED_RGB_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = LED_R_GPIO_PIN;
    GPIO_Init( LED_RGB_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN;
    GPIO_Init( LED_RGB_GPIO_PORT, &GPIO_InitStruct);	

    GPIOB->ODR |= 0x0000FFFF;
}
```
```c
// KEY IO 初始化
void KEY_GPIO_Config(void) {
    GPIO_InitTypeDef	GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);

    GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init( KEY1_GPIO_PORT, &GPIO_InitStruct);
}
```
- 按键检测
```c
uint8_t	Key_Scan(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
    if(GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_PRESS) {
        // 松手检测
        while (GPIO_ReadInputDataBit(GPIOx, GPIO_Pin) == KEY_PRESS) {};		
        return KEY_PRESS;					
    }
    else
        return KEY_RELEASE; 
}
```
- RGB 轮换翻转
```c
#define	 LED_R_TOGGLE	{LED_RGB_GPIO_PORT->ODR ^= LED_R_GPIO_PIN;}
#define	 LED_G_TOGGLE	{LED_RGB_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}
#define	 LED_B_TOGGLE	{LED_RGB_GPIO_PORT->ODR ^= LED_B_GPIO_PIN;}
```
```c
if (Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_PRESS) {	
    switch (led_status) {
        case LED_RED : {
            LED_B_TOGGLE;
            LED_R_TOGGLE;
            break;
        }
        case LED_GREEN : {
            LED_R_TOGGLE;
            LED_G_TOGGLE;
            break;
        }
        case LED_BLUE : {
            LED_G_TOGGLE;
            LED_B_TOGGLE;
            break;
        }
        default :
            break;
    }
    led_status++;
    led_status = led_status % 3;
}  
```