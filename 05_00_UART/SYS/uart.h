#ifndef 	__UART_H
#define		__UART_H

#include	"stm32f10x.h"

#define  BUF_LEN 64

void NVIC_INIT(void);

void USART1_SendString(USART_TypeDef *USARTx, char *str);

void STM_COMInit(void);

#endif //__UART_H
