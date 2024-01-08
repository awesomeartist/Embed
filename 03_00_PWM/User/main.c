#include "stm32f10x.h"
#include "bsp_pwm.h"
#include "time3.h"
#include "bsp_key.h"


int main(void) {
	
	PWM_GPIO_Config( );
	KEY_GPIO_Config( );
    TIM3_Init(TIM3_PSC, TIM3_ARR);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_INIT( );
	EXIT0_INIT( );

	while(1) {}	
}
