#include "stm32f10x.h"
#include "bsp_led.h"
#include "time3.h"

int main(void)
{
	LED_GPIO_Config( );
	NVIC_INIT();
	TIM3_Init(9999,7199);
	
	while(1) {
	}
	
}
