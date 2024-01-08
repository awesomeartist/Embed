#ifndef __BSP_PWM_H

#define __BSP_PWM_H

#include "stm32f10x.h"
#define		TIM3_CH3_GPIO_PIN	GPIO_Pin_0

#define		TIM3_CH3_GPIO_PORT	GPIOB

#define		TIM3_CH3_GPIO_CLK	RCC_APB2Periph_GPIOB

void PWM_GPIO_Config(void);

#endif
