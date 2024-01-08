//bsp:board support package

#include "bsp_pwm.h"

void PWM_GPIO_Config(void) {
	GPIO_InitTypeDef	GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(TIM3_CH3_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = TIM3_CH3_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init( TIM3_CH3_GPIO_PORT, &GPIO_InitStruct);
}
