#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

// 粗略软件延时
void Delay_ms(volatile unsigned int t) {
    unsigned int i, n;
    for (n = 0; n < t; n++)
        for(i = 0; i < 800; i++);
}


int main(void) {	
/*
两种方式配置管脚：
	直接访问配置
	通过别名访问配置
*/
#if 0
	*(unsigned int *)0x40021018 |= ((1) << 3);      // 打开GPIOB端口的时钟
	*(unsigned int *)0x40010C00 |= ((1) << (4*0));  // 配置IO口为输出
	*(unsigned int *)0x40010C0C &= ~(1 << 0);       // 控制ODR寄存器
#elif 0
	RCC_APB2ENR |= ((1) << 3);      // 打开GPIOB端口的时钟
	
	//配置IO口为输出
	GPIOB_CRL &= ~((0x0f) << (4*0));
	GPIOB_CRL |= ((1) << (4*0));
	GPIOB_CRL |= ((1) << (4*1));
	GPIOB_CRL |= ((1) << (4*5));
#endif

/*
两种方式配置连接到LED的管脚：
	通过结构体访问寄存器直接赋值
	通过管脚初始化函数配置
*/
#if 0
	RCC->APB2ENR |= ((1) << 3);         // 打开GPIOB端口的时钟
    
	// 配置IO口为输出
//  GPIOB->CRL &= ~((0x0f) << (4*0));   // 将对应寄存器先置零，再写入
	GPIOB->CRL |= ((1) << (4*0));
	GPIOB->CRL |= ((1) << (4*1));
	GPIOB->CRL |= ((1) << (4*5));
#elif 1
	RCC->APB2ENR |= ((1) << 3);     //开时钟
			
	GPIO_InitTypeDef GPIO_InitStructure;
			
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHZ;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
#endif
	GPIOB->ODR = 0xFFFF;    // 控制ODR寄存器，全部置1，灯灭
	
	while(1) {	
#if 0
    // 通过BSRR与BRR控制灯的亮灭
    GPIOB_BSRR = 0x00000001;
    Delay_ms(1000);
    GPIOB_BRR = 0x00000001;
    Delay_ms(1000);	 		
#endif
/*
两种方式使RGB依次闪烁：
	通过结构体访问ODR控制
    通过置位函数设置
*/			
#if 0			
    GPIOB->ODR = 0xffdf;
    Delay_ms(2000);
    GPIOB->ODR = 0xffff;
    
    GPIOB->ODR = 0xfffe;
    Delay_ms(2000);
    GPIOB->ODR = 0xffff;
    
    GPIOB->ODR = 0xfffd;
    Delay_ms(2000);	
    GPIOB->ODR = 0xffff;
#elif 1
    GPIO_ResetBits(GPIOB, GPIO_Pin_5);
    Delay_ms(2000);
    GPIO_SetBits(GPIOB, GPIO_Pin_5);
    
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
    Delay_ms(2000);
    GPIO_SetBits(GPIOB, GPIO_Pin_0);

    GPIO_ResetBits(GPIOB, GPIO_Pin_1);
    Delay_ms(2000);
    GPIO_SetBits(GPIOB, GPIO_Pin_1);
#endif					
    }
}

void SystemInit(void) {
	// 函数体为空，目的是为了骗过编译器
}

