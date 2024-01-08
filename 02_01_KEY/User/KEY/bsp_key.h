
#ifndef		__BSP_KEY_H
#define		__BSP_KEY_H

#include	"stm32f10x.h"
#define		KEY1_GPIO_PIN   GPIO_Pin_0
#define		KEY1_GPIO_PORT	GPIOA
#define		KEY1_GPIO_CLK	RCC_APB2Periph_GPIOA

#define		KEY_PRESS		(1)
#define		KEY_RELEASE		(0)


void KEY_GPIO_Config(void);
void NVIC_INIT(void);
void EXIT0_INIT(void);

#endif
