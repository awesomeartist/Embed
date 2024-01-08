#include "stm32f10x.h"
#include "bsp_led.h"
#include "time3.h"


int main(void) {	
    LED_GPIO_Config( );
	NVIC_INIT();
	TIM3_Init(7199, 4999);

	while(1) {}
}
