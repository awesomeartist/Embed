

#include "misc.h"
#include "delay.h"

//系统时钟初始化配置
void RCC_Configuration(void)
{
    //定义错误状态变量
   ErrorStatus HSEStartUpStatus;
   //将RCC寄存器重新设置为默认值
   RCC_DeInit();
   //打开外部高速时钟晶振
   RCC_HSEConfig(RCC_HSE_ON);
   //等待外部高速时钟晶振工作
   HSEStartUpStatus = RCC_WaitForHSEStartUp();
   if(HSEStartUpStatus == SUCCESS)
   {
          //设置AHB时钟(HCLK)为系统时钟
          RCC_HCLKConfig(RCC_SYSCLK_Div1);
          //设置高速AHB时钟(APB2)为HCLK时钟
          RCC_PCLK2Config(RCC_HCLK_Div1);
          //设置低速AHB时钟(APB1)为HCLK的2分频（TIM2-TIM5输入TIMxCLK频率将为72MHZ/2x2=72MHZ输入）
          RCC_PCLK1Config(RCC_HCLK_Div2);
          //设置FLASH代码延时
          FLASH_SetLatency(FLASH_Latency_2);
          //使能预取指缓存
          FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
          //设置PLL时钟，为HSE的9倍频 8MHz * 9 = 72MHz
          RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
          //使能PLL
          RCC_PLLCmd(ENABLE);
          //等待PLL准备就绪
          while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
          //设置PLL为系统时钟源
          RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
          //判断PLL是否是系统时钟
          while(RCC_GetSYSCLKSource() != 0x08);
   }
   //允许TIM2的时钟
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
   //允许GPIO的时钟
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
}
