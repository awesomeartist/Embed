#include "stm32f10x.h"
#include <stdio.h>

#include "adc.h"
#include "usart.h"
#include "pwm.h"

uint8_t receive_flag = 0;

int main(void) {

	uint16_t ADC_CH1[64];
	uint16_t ADC_CH2[64];
	uint16_t ADC_CH3[64];
	uint16_t ADC_CH4[64];
	uint8_t receive_data ;
	uint8_t i ;
	
    NVIC_INIT();
	TIM3_Init(TIM3_PSC, TIM3_CH3_ARR);
	
	STM_COMInit();
	printf(" Enter the key to finish the corresponding function\n\r");
	
	ADC_INIT();
	while(1) {	  
		if (receive_flag == 1) {
            receive_flag = 0;
            receive_data = USART_ReceiveData(USART1); 
            USART_SendData(USART1,receive_data); 
            ADC_Out(ADC_CH1, ADC_CH2, ADC_CH3, ADC_CH4);
            printf("\n\r CH1 CH2 CH3 CH4 list below:\n\r");
            for(i = 0;i<64;i++)
                printf("\n %02d \t %04d \t %04d  \t %04d \t %04d",
                    i, ADC_CH1[i], ADC_CH2[i], ADC_CH3[i], ADC_CH4[i]);
		}
	}
}


/*******************************************************************************
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
*******************************************************************************/

int fputc( int ch, FILE *f) {
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART */
    USART_SendData(USART1, (uint8_t) ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}

    return ch;
}
