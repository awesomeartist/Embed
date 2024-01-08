#ifndef __TIME3_H

#define __TIME3_H

#include "stm32f10x.h"

#define TIM2_PSC    (7199)
#define TIM2_ARR    (99)
#define TIM3_PSC    (71)
#define TIM3_ARR    (499)
#define TIM3_PWM_MAX_DUTY TIM3_ARR

void TIM2_Init(uint16_t psc, uint16_t arr);

void TIM3_Init(uint16_t psc, uint16_t arr);

void NVIC_INIT(void);

#endif 
