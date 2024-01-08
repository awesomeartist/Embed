#ifndef __TIME3_H

#define __TIME3_H

#include "stm32f10x.h"

#define TIM3_PSC    (720-1)
#define TIM3_ARR    (2000-1)

void TIM3_Init(uint16_t psc, uint16_t arr);

void NVIC_INIT(void);

#endif 
