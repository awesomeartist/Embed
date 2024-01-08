#include "stm32f10x.h"

#include "led.h"


void LED_INIT(void) {
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(LED_GPIO_PORT_CLK  , ENABLE);  	// ENABLE THE CLOCK FOR PORTB
	
	GPIO_InitStructure.GPIO_Pin = LED_G_PIN; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); 					// ENABLE THE PORT FOR THE GREED LED
	
	GPIO_SetBits(GPIOB, LED_G_PIN);
}
