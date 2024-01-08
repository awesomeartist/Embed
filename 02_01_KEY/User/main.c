#include 	"stm32f10x.h"
#include 	"bsp_led.h"
#include	"bsp_key.h"

int main(void) 
{
	LED_GPIO_Config();
	KEY_GPIO_Config();
    
    NVIC_INIT();
	EXIT0_INIT();
    
    LED_B_TOGGLE;
	while (1) {}	
}
