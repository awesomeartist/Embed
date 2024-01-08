#include 	"bsp_key.h"
#include    "bsp_led.h"

void KEY_GPIO_Config(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK, ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = KEY1_GPIO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;	
	GPIO_Init( KEY1_GPIO_PORT, &GPIO_InitStruct);	
}

void NVIC_INIT(void) {		
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	
	NVIC_Init(&NVIC_InitStructure);
}


void EXIT0_INIT(void) {
	EXTI_InitTypeDef EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA ,GPIO_PinSource0);
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
}

void EXTI0_IRQHandler(void) {			
	if (EXTI_GetITStatus(EXTI_Line0) != 0) {
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
	static uint8_t led_status = 0;
    switch (led_status) {
        case LED_RED : {
            LED_B_TOGGLE;
            LED_R_TOGGLE;
            break;
        }
        case LED_GREEN : {
            LED_R_TOGGLE;
            LED_G_TOGGLE;
            break;
        }
        case LED_BLUE : {
            LED_G_TOGGLE;
            LED_B_TOGGLE;
            break;
        }
        default :
            break;
    }
    led_status++;
    led_status = led_status % 3;  
}
