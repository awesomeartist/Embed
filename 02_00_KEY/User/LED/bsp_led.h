#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f10x.h"

#define  LED_RED    (0)
#define  LED_GREEN  (1)
#define  LED_BLUE   (2)

#define	 LED_G_GPIO_PIN	GPIO_Pin_0
#define	 LED_B_GPIO_PIN	GPIO_Pin_1
#define	 LED_R_GPIO_PIN	GPIO_Pin_5

#define	 LED_RGB_GPIO_PORT	GPIOB

#define	 LED_G_GPIO_CLK	    RCC_APB2Periph_GPIOB

// 实现绿灯翻转宏
#define	 LED_R_TOGGLE	{LED_RGB_GPIO_PORT->ODR ^= LED_R_GPIO_PIN;}
#define	 LED_G_TOGGLE	{LED_RGB_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}
#define	 LED_B_TOGGLE	{LED_RGB_GPIO_PORT->ODR ^= LED_B_GPIO_PIN;}

void LED_GPIO_Config(void);

#endif
