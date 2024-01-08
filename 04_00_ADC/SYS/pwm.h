#ifndef __BSP_PWM_H
#define __BSP_PWM_H

#include "stm32f10x.h"

#define		TIM3_CH3_GPIO_PORT	GPIOB
#define		TIM3_CH3_GPIO_PIN	GPIO_Pin_0
#define		TIM3_CH3_GPIO_CLK	RCC_APB2Periph_GPIOB

#define     TIM3_PSC        (72-1)
#define     TIM3_CH3_ARR    (250-1)

void TIM3_Init(uint16_t psc, uint16_t arr);

#endif
