
#include "stm32f10x.h"
#include "usart.h"

extern uint8_t receive_flag;

void NVIC_INIT(void) {

	NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);             // Configure one bit for preemption priority

    // Enable the USART1 Interrupt
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;           //USART1 INTERRUPT
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   //PreemptionPriority LEVEL 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;          //SubPriority LEVEL 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;             //IRQ CHANNEL ENABLE
	NVIC_Init(&NVIC_InitStructure);                             //INITIALIZE NVIC REGISTER
}

void STM_COMInit(void) {

	USART_InitTypeDef 	USART_InitStructure;
	GPIO_InitTypeDef    GPIO_InitStructure;
	
    // 开串口引脚时钟、管脚复用时钟、串口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO | RCC_APB2Periph_USART1, ENABLE);

    // 配置串口 USART Tx 为复用功能推挽输出模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置串口 USART Rx 为浮空输入模式
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// 配置USART1的一些参数：波特率、字长、停止位、
    USART_InitStructure.USART_BaudRate = 19200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);           // 串口初始化
    
    // 开USART1输入中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
   
    // 使能USART1
    USART_Cmd(USART1, ENABLE);
}

void USART1_IRQHandler(void) {
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		USART_ClearFlag(USART1, USART_IT_RXNE);
		receive_flag = 1;
	}
}

