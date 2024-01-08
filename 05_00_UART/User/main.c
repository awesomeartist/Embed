#include "stm32f10x.h"
#include "uart.h"
#include "led.h"

uint8_t receive_data = 0;
char usart_rx_buf[BUF_LEN];

int main(void)
{ 
	NVIC_INIT( );
	STM_COMInit( );
	LED_INIT( );
	
	while (1) {
		if (receive_data) {					
			GPIO_ResetBits(LED_GPIO_PORT, LED_G_PIN);
			USART1_SendString(USART1, usart_rx_buf);
			GPIO_SetBits(LED_GPIO_PORT, LED_G_PIN);
			receive_data = 0;
		}						
	}	
}
