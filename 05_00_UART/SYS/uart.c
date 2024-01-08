#include	"stm32f10x.h"
#include	"uart.h"
#include	"led.h"

extern uint8_t receive_data;
uint8_t usart_rx_len = 0;
extern char usart_rx_buf[BUF_LEN];

// 串口中断初始化
void NVIC_INIT(void){
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);	
}
// USART1初始化
void STM_COMInit(void) {
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);
	// Tx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	// Rx
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 19200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_Init(USART1, &USART_InitStructure);
	// 开USART1数据接收接寄存器非空中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_Cmd(USART1, ENABLE);
}


// 发送字符串到串口USARTx,并以换行符结束
void USART1_SendString(USART_TypeDef *USARTx, char *str) {
	while(*str != '\0') {
		USART_SendData(USARTx, *str++);
		// 等待字符发送完成，先读取SR检查发送数据寄存器是否为空，即数据是否已经转移到移位寄存器中
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
	}
	// 等待字符发送完成，当数据发送完成并且TXE=1时，由硬件置1；
	// 由于复位值为1，如果不清除标志位，或者读SR寄存器检查发送数据寄存器判断数据是否已写入移位寄存器，第一个字节会被覆盖
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	USART_SendData(USARTx, '\r');
}

// USART1接收以\n或\r结尾的字符串，并存入字符串数组
void USART1_IRQHandler(void) {
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
		usart_rx_buf[usart_rx_len] = USART_ReceiveData(USART1);
		usart_rx_len++;
		if (usart_rx_len >= BUF_LEN)
			usart_rx_len = 0;
		
		if (usart_rx_len > 0)
			if((usart_rx_buf[usart_rx_len-1] == '\r') || (usart_rx_buf[usart_rx_len-1] == '\n')) {
				usart_rx_len--;
				usart_rx_buf[usart_rx_len] = '\0';
				usart_rx_len = 0;
				receive_data = 1;
			}						
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);	
	}			
}

// 程序运行，串口调试助手发送字符串"abcdefgh"，串口调试助手收到的是"a\/b\/e\/h\/
#if 0
void USART1_IRQHandler(void) {	
	static uint8_t i = 0;	
	receive_data = USART_ReceiveData(USART1); 
	// 清除标志位
	USART_ClearFlag(USART1, USART_FLAG_TC);
		
	USART_SendData(USART1, receive_data);
	// 等待字符发送完成，先读取SR检查发送数据寄存器是否为空，即数据是否已经转移到移位寄存器中
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, '\\');
	
	// 等待字符发送完成，当数据发送完成并且TXE=1时，由硬件置1；
	// 由于复位值为1，如果不清除标志位，或者读SR寄存器检查发送数据寄存器判断数据是否已写入移位寄存器，第一个字节会被覆盖
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	USART_SendData(USART1, '/');
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
		
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {	
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}		
}
// 程序运行，串口调试助手发送字符串 abcdefghijk，串口调试助手收到 a00b00d00g00j00
#elif 0
void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {	
        receive_data = USART_ReceiveData(USART1);
    }	
        receive_data = USART_ReceiveData(USART1);	
        USART_SendData(USART1, receive_data);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, '0');
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
        USART_SendData(USART1, '0');
        while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
    
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {	
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    }		
}
#endif
