#include "stm32f10x.h"
#include "pwm.h"

// TIM3产生PWM波 
void TIM3_Init(uint16_t psc, uint16_t arr) {
	GPIO_InitTypeDef	    GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef       TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(TIM3_CH3_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = TIM3_CH3_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init( TIM3_CH3_GPIO_PORT, &GPIO_InitStruct);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		    // TIM3时钟使能
	TIM_TimeBaseStructure.TIM_Period = arr;			                // 计时周期
	TIM_TimeBaseStructure.TIM_Prescaler = psc;		                // TIM3分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;		            // 系统时钟分频，未分频，为72MHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	    // 计数模式为向上计数
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);		            // 初始化TIM3

	// TIM3 PWM  CH3 配置
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 100-1;                          // 设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);	
	
	TIM_ARRPreloadConfig(TIM3, ENABLE);                             // 使能TIM3在ARR上的预装载寄存器
	TIM_Cmd(TIM3, ENABLE);	                                        // 使能TIM3
}
