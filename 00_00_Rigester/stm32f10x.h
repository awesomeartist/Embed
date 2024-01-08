// 寄存器映射

// 外设periphral，地址映射
#ifndef __STM32F10X_H
#define __STM32F10X_H

#define PERIPH_BASE			((unsigned int)0x40000000)
#define APB1_PERIPH_BASE	PERIPH_BASE
#define APB2_PERIPH_BASE	(PERIPH_BASE + 0x10000)
#define AHB_PERIPH_BASE		(PERIPH_BASE + 0x20000)


#define RCC_BASE		(AHB_PERIPH_BASE + 0x1000)
#define GPIOB_BASE		(APB2_PERIPH_BASE + 0x0C00)


/*
这段用于对寄存器映射，能够间接访问寄存器
(unsigned int*)(GPIOB_BASE+0x00)    把地址强制转换成指针类型
*(unsigned int*)(GPIOB_BASE+0x00)   把地址强制转换成指针类型并指向该地址  
“*” 作用是解引用，引用指针指向的变量值，引用其实就是引用该变量的地址。
*/	
#define RCC_APB2ENR	    *(unsigned int*)(RCC_BASE + 0x18)
	
#define GPIOB_CRL		*(unsigned int*)(GPIOB_BASE + 0x00) // 端口配置低寄存器
#define GPIOB_CRH		*(unsigned int*)(GPIOB_BASE + 0x04) // 端口配置高寄存器
#define GPIOB_IDR		*(unsigned int*)(GPIOB_BASE + 0x08) // 端口输入数据寄存器
#define GPIOB_ODR		*(unsigned int*)(GPIOB_BASE + 0x0C) // 端口输出数据寄存器
#define GPIOB_BSRR		*(unsigned int*)(GPIOB_BASE + 0x10) // 端口位设置/清除寄存器
#define GPIOB_BRR		*(unsigned int*)(GPIOB_BASE + 0x14) // 端口位清除寄存器
#define GPIOB_LCKR		*(unsigned int*)(GPIOB_BASE + 0x18) // 端口配置锁定寄存器

/*
这段完成对GPIO管脚结构体的定义，以及时钟结构体定义
初始化结构后可通过结构体访问寄存器
*/
typedef unsigned int 		uint32_t;
typedef unsigned short 		uint16_t;

typedef struct {
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;
}GPIO_TypeDef;

#define GPIOB   ((GPIO_TypeDef *)GPIOB_BASE)

typedef struct {
	uint32_t CR;        // 时钟控制寄存器
	uint32_t CFGR;      // 时钟配置寄存器
	uint32_t CIR;       // 时钟中断寄存器
	uint32_t APB2RSTR;  // APB2 外设复位寄存器
	uint32_t APB1RSTR;  // APB1 外设复位寄存器
	uint32_t AHBENR;    // AHB 外设时钟使能寄存器
	uint32_t APB2ENR;   // APB2 外设时钟使能寄存器
	uint32_t APB1ENR;   // APB1 外设时钟使能寄存器
	uint32_t ABDCR;     // 备份域控制寄存器
	uint32_t CSR;       // 控制状态寄存器
	uint32_t AHBRSTR;
	uint32_t CFGR2;
}RCC_TypeDef;

#define RCC	 ((RCC_TypeDef *)RCC_BASE)

#endif//__STM32F10X_H
