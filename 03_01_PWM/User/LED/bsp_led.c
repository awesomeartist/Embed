//bsp:board support package

#include "bsp_led.h"

void LED_GPIO_Config(void) {
	GPIO_InitTypeDef	GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(LED_RGB_GPIO_CLK, ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    // 使能复用时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);    // TIMER3 部分重映射
	// 红灯
	GPIO_InitStruct.GPIO_Pin = LED_R_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init( LED_RGB_GPIO_PORT, &GPIO_InitStruct);
	// 蓝灯
	GPIO_InitStruct.GPIO_Pin = LED_B_GPIO_PIN;
	GPIO_Init( LED_RGB_GPIO_PORT, &GPIO_InitStruct);
	
	// 红灯
	GPIO_InitStruct.GPIO_Pin = LED_G_GPIO_PIN;
	GPIO_Init( LED_RGB_GPIO_PORT, &GPIO_InitStruct);
	
	GPIOB->ODR |= 0x0000FFFF;
	
}
