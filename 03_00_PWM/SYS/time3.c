#include "time3.h"
#include "bsp_pwm.h"


void TIM3_Init(uint16_t psc, uint16_t arr) {
    
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		// TIM3时钟使能
	TIM_TimeBaseStructure.TIM_Period = arr;			            // 计时周期
	TIM_TimeBaseStructure.TIM_Prescaler = psc;		            // TIM3分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;		        // 系统时钟分频，未分频，为72MHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 计数模式为向上计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);		        // 初始化TIM3
	
	// TIM3 PWM配置
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 150-1; // 设置待装入捕获比较寄存器的脉冲值

	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;   // 用于控制舵机
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
		
	TIM_ARRPreloadConfig(TIM3, ENABLE);     // 使能TIM3在ARR上的预装载寄存器
		
	TIM_Cmd(TIM3, ENABLE);	  // 使能TIM3
}
