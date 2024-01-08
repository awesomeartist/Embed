### 一、开发环境
- 开发板：野火指南者
- IDE：keil MDKv5
- 开发方式：标准库开发

### 二、功能实现
使用 TIMER2/TIMER3 实现 RGB 按色环上颜色变换  
TIMER3 输出 PWN 驱动 RGB，TIMER2 产生中断改变各个通道 PWN 占空比

### 三、实现思路
- IO 初始化
```c
    GPIO_InitTypeDef	GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(LED_RGB_GPIO_CLK, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    // 使能复用时钟

    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);    // TIMER3 部分重映射
    // 红灯
    GPIO_InitStruct.GPIO_Pin = LED_R_GPIO_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
```
- TIMER2 初始化
```c
void TIM2_Init(uint16_t psc, uint16_t arr) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);        // TIM2时钟使能
    TIM_TimeBaseStructure.TIM_Period = arr;		        // 计时周期
    TIM_TimeBaseStructure.TIM_Prescaler = psc;		        // TIM2分频
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;		        // 系统时钟分频，未分频，为72MHz
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 计数模式为向上计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);		// 初始化TIM2

    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		        // 使能TIM2中断更新
        
    TIM_Cmd(TIM2, ENABLE);	  // 使能TIM2
}
```
- TIMER2 中断配置
```c
void NVIC_INIT(void) {
    NVIC_InitTypeDef NVIC_InitStruct;
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	    // 中断分组		
    NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;	    // TIM2 中断向量
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	    // 使能中断
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;  // 中断抢占优先级
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;	    // 中断响应优先级
		
    NVIC_Init(&NVIC_InitStruct);    // 初始化中断
}
```
- TIMER3 初始化与 PWM 初始化
```c
void TIM3_Init(uint16_t psc, uint16_t arr) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    TIM_TimeBaseStructure.TIM_Period = arr;
    TIM_TimeBaseStructure.TIM_Prescaler = psc;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // TIM3 PWM配置
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 250-1;                      // 设置待装入捕获比较寄存器的脉冲值
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    // 红色
    TIM_OC2Init(TIM3,&TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
    // 绿色
    TIM_OC3Init(TIM3,&TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
    // 蓝色
    TIM_OC4Init(TIM3,&TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);		
        
    TIM_ARRPreloadConfig(TIM3, ENABLE);                         // 使能TIM3在ARR上的预装载寄存器	
    TIM_Cmd(TIM3, ENABLE);	                                // 使能TIM3
}
```
- TIMER2 中断服务函数
```c
void TIM2_IRQHandler(void) {
    // 检查指定的TIM中断是否发生
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {		
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		    // 清除中断标志位
    }
        
    static uint16_t red_duty;        // 亮度标记，PWM 占空比
    static uint16_t green_duty;
    static uint16_t blue_duty;
    static uint8_t flag = 0;

    if (flag == 0) {
        green_duty = 499 - red_duty;
        red_duty++;
        if (red_duty > 499) {
            flag++;
            flag = flag % 3;
        }
        blue_duty = 0;
    }
    if (flag == 1) {
        red_duty = 499 - blue_duty;
        blue_duty++;
        if (blue_duty > 499) {
            flag++;
            flag = flag % 3;
        }
        green_duty = 0;
    }
    if (flag == 2) {
        blue_duty = 499 - green_duty;
        green_duty++;
        if (green_duty > 499) {
            flag++;
            flag = flag % 3;
        }
        red_duty = 0;
    }    

    TIM_SetCompare2(TIM3, red_duty);
    TIM_SetCompare3(TIM3, green_duty);
    TIM_SetCompare4(TIM3, blue_duty);
}
```