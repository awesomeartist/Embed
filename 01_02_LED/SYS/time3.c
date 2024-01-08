#include "time3.h"
#include "bsp_led.h"

void TIM3_Init(uint16_t psc, uint16_t arr) {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);		// TIM3时钟使能
	TIM_TimeBaseStructure.TIM_Period = arr;			            // 计时周期
    TIM_TimeBaseStructure.TIM_Prescaler = psc;		            // TIM3分频
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;		        // 系统时钟分频，未分频，为72MHz
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 计数模式为向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);		        // 初始化TIM3
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		            // 使能TIM3中断更新
		
	TIM_Cmd(TIM3, ENABLE);	  // 使能TIM3
}


void NVIC_INIT(void) {
	NVIC_InitTypeDef NVIC_InitStruct;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				// 中断分组
		
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;				// TIM3中断向量
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;				// 使能中断
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;		// 中断抢占优先级
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;				// 中断响应优先级
		
	NVIC_Init(&NVIC_InitStruct);		// 初始化中断
}

// TIM3中断服务函数
void TIM3_IRQHandler(void) {
    // 检查指定的TIM中断是否发生
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);		// 清除中断标志位
	}	
	static uint8_t i = 0;
	switch (i) {
		case 0:GPIO_SetBits(LED_RGB_GPIO_PORT, LED_B_GPIO_PIN);
               GPIO_ResetBits(LED_RGB_GPIO_PORT, LED_G_GPIO_PIN);i++; break;
						
		case 1:GPIO_SetBits(LED_RGB_GPIO_PORT, LED_G_GPIO_PIN);
			   GPIO_ResetBits(LED_RGB_GPIO_PORT, LED_R_GPIO_PIN);i++; break;
						
		case 2:GPIO_SetBits(LED_RGB_GPIO_PORT, LED_R_GPIO_PIN);
			   GPIO_ResetBits(LED_RGB_GPIO_PORT, LED_B_GPIO_PIN);i = 0; break;					
	}		
}
