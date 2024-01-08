
#include "stm32f10x.h"
#include "adc.h"
#include "usart.h"

__IO uint16_t 	    ADCConvertedValueTab[64];

GPIO_InitTypeDef    GPIO_InitStructure;
ADC_InitTypeDef     ADC_InitStructure;
DMA_InitTypeDef     DMA_InitStructure;

// 初始化ADC1
void ADC_INIT(void) {
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = ADC_CH1_Pin | ADC_CH2_Pin |ADC_CH3_Pin | ADC_CH1_Pin;		
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			 								
    GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure); 
     
    DMA_InitStructure.DMA_PeripheralBaseAddr = ADC_DataRegister;	              			// 外设地址，ACD_N的数据寄存器
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADCConvertedValueTab;   				// 目标地址
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;				  						// DMA方向，外设为源
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;						// 外设（内部FLASH）地址递增，失能
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;									// 内存地址递增，使能
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  			// 外设数据单位16位
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;  					// DMA内存数据单位,HalfWord=16位
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;   										// DMA模式，一次或循环模式，BufferSize
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;										// DMA优先级高
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;		  									// M2M失能内存到内存
    DMA_InitStructure.DMA_BufferSize = 64; 
     
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;										// 只是用ADC1，选独立模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;		  									// 多通道，使用扫描模式
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;   									// 连续转换模式
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;						// ADC不用外部触发转换，软件开启
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  								// 转换结果右对齐
    ADC_InitStructure.ADC_NbrOfChannel = 1;	 												// 转换通道，1个
    ADC_Init(ADC_N, &ADC_InitStructure);
    ADC_DMACmd(ADC_N, ENABLE); 
  
	// 开启ADC，并开始转换
	ADC_Cmd(ADC_N, ENABLE);                         
    ADC_ResetCalibration(ADC_N);	                // 初始化ADC校准器
    while(ADC_GetResetCalibrationStatus(ADC_N));    // 等待较准器初始化完成
    ADC_StartCalibration(ADC_N);	                // ADC开始校准
    while(ADC_GetCalibrationStatus(ADC_N));	        // 等待校准完成
	
}

// 逐个通道采集并通过DMA传送
void ADC_Out(uint16_t* Value1, uint16_t* Value2, uint16_t* Value3, uint16_t* Value4) {

	uint16_t count;
	
	// ADC1_CH1
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);               // 配置ADC时钟为PCLK2的8分频，系统时钟为72MHz，即9MHz
	DMA_DeInit(DMA1_Channel1);	                    // 重置DMA1_Channel1的寄存器为默认值	 
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);    // 初始化DMA1
    DMA_Cmd(DMA1_Channel1, ENABLE);                 // 使能DMA1
	
	// 配置ADC通道准换顺序和采样时间
    // Setting the sampling frequency. 
    ADC_RegularChannelConfig(ADC_N, ADC_Channel_10, 1, ADC_SampleTime_71Cycles5);
	ADC_SoftwareStartConvCmd(ADC_N, ENABLE);        // 没有采用外部触发，使用软件触发ADC转换
	
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1)) {}  	// 等待DMA传送完成
    ADC_SoftwareStartConvCmd(ADC_N, DISABLE);       // ADC软件失能
    DMA_Cmd(DMA1_Channel1, DISABLE);            	// DMA1_Channel1失能
    DMA_ClearFlag(DMA1_FLAG_TC1);                   // 清除DMA1传送完成标志TC1	
    for (count = 0; count < 64; count++) {
		Value1[count] =  ADCConvertedValueTab[count];
	}
	
	// ADC1_CH2
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	DMA_DeInit(DMA1_Channel1);
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);      
    DMA_Cmd(DMA1_Channel1, ENABLE);
	
 	ADC_RegularChannelConfig(ADC_N, ADC_Channel_12, 1, ADC_SampleTime_71Cycles5);
	ADC_SoftwareStartConvCmd(ADC_N, ENABLE);
	
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1)) {}
    ADC_SoftwareStartConvCmd(ADC_N, DISABLE);
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA_ClearFlag(DMA1_FLAG_TC1);
	
	for (count = 0; count < 64; count++) {
		Value2[count] =  ADCConvertedValueTab[count];
	}
	
	// ADC1_CH3
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	DMA_DeInit(DMA1_Channel1);
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);      
    DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_RegularChannelConfig(ADC_N, ADC_Channel_13, 1, ADC_SampleTime_71Cycles5);
	ADC_SoftwareStartConvCmd(ADC_N, ENABLE);
	
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1)) {}
    ADC_SoftwareStartConvCmd(ADC_N, DISABLE);
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA_ClearFlag(DMA1_FLAG_TC1);
	
	for (count = 0; count < 64; count++) {
		Value3[count] = ADCConvertedValueTab[count];
	}
	// ADC1_CH4
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	DMA_DeInit(DMA1_Channel1);
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);      
    DMA_Cmd(DMA1_Channel1, ENABLE);
	
	ADC_RegularChannelConfig(ADC_N, ADC_Channel_14, 1, ADC_SampleTime_71Cycles5);
	ADC_SoftwareStartConvCmd(ADC_N, ENABLE);
	
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC1)) {}
    ADC_SoftwareStartConvCmd(ADC_N, DISABLE);
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA_ClearFlag(DMA1_FLAG_TC1);
	for (count = 0; count < 64; count++) {
		Value4[count] = ADCConvertedValueTab[count];
	}
}
