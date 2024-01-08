#ifndef __BSP_LED_H

#define __BSP_LED_H

#include "stm32f10x.h"
#define	LED_RGB_GPIO_PORT	GPIOC
#define	LED_G_GPIO_PIN	    GPIO_Pin_13

#define	LED_G_GPIO_CLK	    RCC_APB2Periph_GPIOC

void LED_GPIO_Config(void);
#endif
