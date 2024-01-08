### 一、开发环境
- 开发板：野火指南者
- IDE：keil MDKv5
- 开发方式：标准库开发

### 二、功能实现
while 循环内读 KEY1 对应 IO 输入，RGB 颜色切换

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
- 外部中断配置
```c
void NVIC_INIT(void) {		
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;

    NVIC_Init(&NVIC_InitStructure);
}


void EXIT0_INIT(void) {
    EXTI_InitTypeDef EXTI_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA ,GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init(&EXTI_InitStructure);
}
```
- RGB 轮换翻转
```c
#define	 LED_R_TOGGLE	{LED_RGB_GPIO_PORT->ODR ^= LED_R_GPIO_PIN;}
#define	 LED_G_TOGGLE	{LED_RGB_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}
#define	 LED_B_TOGGLE	{LED_RGB_GPIO_PORT->ODR ^= LED_B_GPIO_PIN;}
```
```c
void EXTI0_IRQHandler(void) {			
    if (EXTI_GetITStatus(EXTI_Line0) != 0) {
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
    static uint8_t led_status = 0;
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