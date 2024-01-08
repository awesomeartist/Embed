#include "stm32f10x.h"

#include "bsp_led.h"

//不准确的软件延时,ms
void Delay(uint32_t Num) {
	for(int i = Num; i > 0; i--) {
		for(int j = 8000; j > 0; j--);
	}
}

int main(void)
{
	 LED_GPIO_Config( );

	while(1) {	
		GPIO_ResetBits(LED_RGB_GPIO_PORT, LED_G_GPIO_PIN);
		Delay(1000);
		GPIO_SetBits(LED_RGB_GPIO_PORT, LED_G_GPIO_PIN);
		Delay(1000);
	}
}
