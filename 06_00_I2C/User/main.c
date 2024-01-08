#include "stm32f10x.h"
#include "bsp_i2c_ee.h"
#include "bsp_usart.h"
#include "stdio.h"

#define ROM_ADDRESS (0x00)
#define Buffer_Size    (8)

void Show_BufferRead(uint8_t *str, uint16_t length);

int main(void)
{   
    uint8_t Buffer_Read[16];
    uint8_t Buffer_Write_0[16] = "01234567";
    uint8_t Buffer_Write_1[16] = "hello world!";
    
    STM_COMInit();
    printf("I2C 通讯测试\n");
    
    I2C_EE_Init();
    I2C_EE_ByteWrite(Buffer_Write_0, ROM_ADDRESS);
    I2C_EE_BytesWrite(Buffer_Write_0, ROM_ADDRESS, Buffer_Size);
    I2C_EE_BufferRead(Buffer_Read, ROM_ADDRESS, Buffer_Size);
    Show_BufferRead(Buffer_Read, Buffer_Size);
    
    I2C_EE_PageWrite(Buffer_Write_1, ROM_ADDRESS, Buffer_Size);
    I2C_EE_BufferRead(Buffer_Read, ROM_ADDRESS, Buffer_Size);
    Show_BufferRead(Buffer_Read, Buffer_Size);
}


void Show_BufferRead(uint8_t *str, uint16_t length)
{   
    printf("\nBufferRead\n");
    for (int i = 0; i < length; i++) {
        printf("[0x%02x] = %c\n", ROM_ADDRESS + i, str[i]);
    }
}
