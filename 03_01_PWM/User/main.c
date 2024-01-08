#include "stm32f10x.h"
#include "bsp_led.h"
#include "time3.h"

int main(void) {
	
	LED_GPIO_Config( );
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 中断分组
	NVIC_INIT();
	
	TIM2_Init(TIM2_PSC, TIM2_ARR);
	TIM3_Init(TIM3_PSC, TIM3_ARR);

	while(1) {}
}
