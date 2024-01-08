#ifndef BSP_I2C_EE_H
#define BSP_I2C_EE_H

#include    "stm32f10x.h"

/**************************I2C参数定义，I2C1或I2C2*********************/
#define       EEPROM_I2Cx                       I2C1
#define       EEPROM_I2C_APBxClock_FUN          RCC_APB1PeriphClockCmd
#define       EEPROM_I2C_CLK                    RCC_APB1Periph_I2C1
#define       EEPROM_I2C_GPIO_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define       EEPROM_I2C_GPIO_CLK               RCC_APB2Periph_GPIOB
#define       EEPROM_I2C_SCL_PORT               GPIOB
#define       EEPROM_I2C_SCL_PIN                GPIO_Pin_6
#define       EEPROM_I2C_SDA_PORT               GPIOB
#define       EEPROM_I2C_SDA_PIN                GPIO_Pin_7

/* STM32 I2C 快速模式 */
#define I2C_Speed              400000  //*

/* 这个地址只要与STM32外挂的I2C器件地址不一样即可 */
#define I2Cx_OWN_ADDRESS7      0X0A

#define EEPROM_ADDRESS          0xA0

/* AT24C01/02每页有8个字节 */
#define I2C_PageSize           8

void I2C_EE_Init(void);
uint32_t I2C_EE_ByteWrite(u8* pBuffer, u8 WriteAddr);
uint8_t I2C_EE_BytesWrite(uint8_t* pBuffer,uint8_t WriteAddr, uint16_t NumByteToWrite);
void I2C_EE_WaitEepromStandbyState(void);
uint8_t I2C_EE_PageWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite);
void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite);
uint8_t I2C_EE_BufferRead(uint8_t* pBuffer, uint8_t ReadAddr, u16 NumByteToRead);


#endif
