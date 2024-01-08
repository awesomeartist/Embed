#ifndef __ADC_H

#define __ADC_H

#include "stm32f10x.h"

#define ADC_N ADC1
#define ADC_GPIO_PORT GPIOC
#define ADC_CH1_Pin GPIO_Pin_1
#define ADC_CH2_Pin GPIO_Pin_2
#define ADC_CH3_Pin GPIO_Pin_3
#define ADC_CH4_Pin GPIO_Pin_4

#define ADC_DataRegister ((uint32_t)0x4001244C)


void ADC_INIT(void);

void ADC_Out(uint16_t* Value1, uint16_t* Value2, 
			 uint16_t* Value3, uint16_t* Value4);


#endif
