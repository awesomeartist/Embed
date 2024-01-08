#include "time3.h"
#include "bsp_led.h"

void TIM2_Init(uint16_t psc, uint16_t arr) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);		// TIM2时钟使能
	TIM_TimeBaseStructure.TIM_Period = arr;			            // 计时周期
	TIM_TimeBaseStructure.TIM_Prescaler = psc;		            // TIM2分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;		        // 系统时钟分频，未分频，为72MHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 计数模式为向上计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);		        // 初始化TIM2
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		            // 使能TIM2中断更新
		
	TIM_Cmd(TIM2, ENABLE);	  // 使能TIM2
}

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
	TIM_Cmd(TIM3, ENABLE);	                                    // 使能TIM3
}



void NVIC_INIT(void) {
	NVIC_InitTypeDef NVIC_InitStruct;
		
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;			// TIM2中断向量
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;			// 使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;	// 中断抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;			// 中断响应优先级
		
	NVIC_Init(&NVIC_InitStruct);		                    // 初始化中断
}

// TIM2中断服务函数
void TIM2_IRQHandler(void) {
    // 检查指定的TIM中断是否发生
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		    // 清除中断标志位
	}
        
    static uint16_t red_duty;    // 亮度标记，PWM 占空
    static uint16_t green_duty;
    static uint16_t blue_duty;
    static uint8_t flag = 0;

    if (flag == 0) {
        green_duty = TIM3_PWM_MAX_DUTY - red_duty;
        red_duty++;
        if (red_duty > TIM3_PWM_MAX_DUTY) {
            flag++;
            flag = flag % 3;
        }
        blue_duty = 0;
    }
    if (flag == 1) {
        red_duty = TIM3_PWM_MAX_DUTY - blue_duty;
        blue_duty++;
        if (blue_duty > TIM3_PWM_MAX_DUTY) {
            flag++;
            flag = flag % 3;
        }
        green_duty = 0;
    }
    if (flag == 2) {
        blue_duty = TIM3_PWM_MAX_DUTY - green_duty;
        green_duty++;
        if (green_duty > TIM3_PWM_MAX_DUTY) {
            flag++;
            flag = flag % 3;
        }
        red_duty = 0;
    }    

    TIM_SetCompare2(TIM3, red_duty);
    TIM_SetCompare3(TIM3, green_duty);
    TIM_SetCompare4(TIM3, blue_duty);
}
