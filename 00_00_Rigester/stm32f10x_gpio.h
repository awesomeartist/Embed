#ifndef		__STM32F10X_GPIO_H
#define		__STM32F10X_GPIO_H

#include "stm32f10x.h"

#define GPIO_Pin_0		((uint16_t)0x0001)	//选择Pin_0
#define GPIO_Pin_1		((uint16_t)0x0002)	//选择Pin_1
#define GPIO_Pin_2		((uint16_t)0x0004)	//选择Pin_2
#define GPIO_Pin_3		((uint16_t)0x0008)	//选择Pin_3
#define GPIO_Pin_4		((uint16_t)0x0010)	//选择Pin_4
#define GPIO_Pin_5		((uint16_t)0x0020)	//选择Pin_5
#define GPIO_Pin_6		((uint16_t)0x0040)	//选择Pin_6
#define GPIO_Pin_7		((uint16_t)0x0080)	//选择Pin_7

#define GPIO_Pin_8		((uint16_t)0x0100)	//选择Pin_8
#define GPIO_Pin_9		((uint16_t)0x0200)	//选择Pin_9
#define GPIO_Pin_10		((uint16_t)0x0400)	//选择Pin_10
#define GPIO_Pin_11		((uint16_t)0x0800)	//选择Pin_11
#define GPIO_Pin_12		((uint16_t)0x1000)	//选择Pin_12
#define GPIO_Pin_13		((uint16_t)0x2000)	//选择Pin_13
#define GPIO_Pin_14		((uint16_t)0x4000)	//选择Pin_14
#define GPIO_Pin_15		((uint16_t)0x8000)	//选择Pin_15

#define GPIO_Pin_All	((uint16_t)0xffff)	//选择Pin_All

typedef enum {
	GPIO_Speed_10MHZ = 1,
	GPIO_Speed_2MHZ,
	GPIO_Speed_50MHZ	
}GPIOSpeed_TypeDef;

typedef enum {
	GPIO_Mode_AIN = 0x0,			//模拟输入
	GPIO_Mode_IN_FLOATING = 0x04,	//浮空输入
	GPIO_Mode_IPD = 0x28,			//下拉输入
	GPIO_Mode_IPU = 0x48,			//上拉输入
	
	GPIO_Mode_Out_OD = 0x14,		//开漏输出
	GPIO_Mode_Out_PP = 0x10,		//推挽输出
	GPIO_Mode_AF_OD = 0x1C,			//复用开漏输出
	GPIO_Mode_AF_PP = 0x18			//复用推挽输出
	
}GPIOMode_TypeDef;

typedef struct {
	uint16_t GPIO_Pin;
	uint16_t GPIO_Speed;
	uint16_t GPIO_Mode;
}GPIO_InitTypeDef;


void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);

#endif //__STM32F10X_GPIO_H
