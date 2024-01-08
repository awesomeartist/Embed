#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

#define LED_GPIO_PORT	GPIOB

#define LED_GPIO_PORT_CLK	RCC_APB2Periph_GPIOB

#define LED_G_PIN  GPIO_Pin_0

void LED_INIT(void);


#endif
