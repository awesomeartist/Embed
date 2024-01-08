
#include    "bsp_i2c_ee.h"
#include    "stm32f10x.h"
#include    "stdio.h"

uint32_t    I2CTimeout;

static void I2C_GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* 使能与 I2C 有关的时钟 */
    EEPROM_I2C_APBxClock_FUN ( EEPROM_I2C_CLK, ENABLE );
    EEPROM_I2C_GPIO_APBxClock_FUN ( EEPROM_I2C_GPIO_CLK, ENABLE );

    /* I2C_SCL、I2C_SDA*/
    GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN | EEPROM_I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(EEPROM_I2C_SDA_PORT, &GPIO_InitStructure);
}

/**
* @brief  I2C 工作模式配置
* @param  无
* @retval 无
*/
static void I2C_Mode_Config(void)
{
    I2C_InitTypeDef  I2C_InitStructure;

    /* I2C 配置 */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;

    /* 高电平数据稳定，低电平数据变化 SCL 时钟线的占空比 */
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;

    I2C_InitStructure.I2C_OwnAddress1 =I2Cx_OWN_ADDRESS7;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable ;

    /* I2C的寻址模式 */
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;

    /* 通信速率 */
    I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;

    /* I2C 初始化 */
    I2C_Init(EEPROM_I2Cx, &I2C_InitStructure);

    /* 使能 I2C */
    I2C_Cmd(EEPROM_I2Cx, ENABLE);
}


/**
* @brief  I2C 外设(EEPROM)初始化
* @param  无
* @retval 无
*/
void I2C_EE_Init(void)
{
    I2C_GPIO_Config();

    I2C_Mode_Config();

}

/***************************************************************/
/*通讯等待超时时间*/
#define I2CT_FLAG_TIMEOUT   ((uint32_t)0x1000)
#define I2CT_LONG_TIMEOUT   ((uint32_t)(10 * I2CT_FLAG_TIMEOUT))

/**
* @brief  I2C等待事件超时的情况下会调用这个函数来处理
* @param  errorCode：错误代码，可以用来定位是哪个环节出错.
* @retval 返回0，表示IIC读取失败.
*/
static  uint32_t I2C_TIMEOUT_UserCallback(uint8_t errorCode)
{
    /* 使用串口printf输出错误信息，方便调试 */
    printf("I2C 等待超时!errorCode = %d\n", errorCode);
    return 0;
}
/**
* @brief   写一个字节到I2C EEPROM中
* @param   pBuffer:缓冲区指针
* @param   WriteAddr:写地址
* @retval  正常返回1，异常返回0
*/
uint32_t I2C_EE_ByteWrite(u8* pBuffer, u8 WriteAddr)
{
    /* 产生I2C起始信号 */
    I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);

    /*设置超时等待时间*/
    I2CTimeout = I2CT_FLAG_TIMEOUT;
    
    /* 检测 EV5 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT)) {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(0);
    }

    /* 发送EEPROM设备地址 */
    I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);

    I2CTimeout = I2CT_FLAG_TIMEOUT;
    /* 检测 EV6 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(1);
    }

    /* 发送要写入的EEPROM内部地址(即EEPROM内部存储器的地址) */
    I2C_SendData(EEPROM_I2Cx, WriteAddr);

    I2CTimeout = I2CT_FLAG_TIMEOUT;
    
    /* 检测 EV8 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(2);
    }
    
    /* 发送一字节要写入的数据 */
    I2C_SendData(EEPROM_I2Cx, *pBuffer);

    I2CTimeout = I2CT_FLAG_TIMEOUT;
    /* 检测 EV8 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
    }

    /* 发送停止信号 */
    I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
    
    /* 等待 EEPROM 写入完成 */
    I2C_EE_WaitEepromStandbyState();

    return 1;
}

uint8_t I2C_EE_BytesWrite(uint8_t* pBuffer,uint8_t WriteAddr, uint16_t NumByteToWrite)
{
    uint16_t i;
    uint8_t res;
    /*每写一个字节调用一次I2C_EE_ByteWrite函数*/
    for (i=0; i<NumByteToWrite; i++)
    {
        /*等待EEPROM准备完毕*/
        I2C_EE_WaitEepromStandbyState();
        /*按字节写入数据*/
        res = I2C_EE_ByteWrite(pBuffer++,WriteAddr++);
    }
    return res;
}

/**
* @brief  等待EEPROM到准备状态
* @param  无
* @retval 无
*/
void I2C_EE_WaitEepromStandbyState(void)
{
    vu16 SR1_Tmp = 0;

    do {
        /* 发送起始信号 */
        I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);

        /* 读 I2C1 SR1 寄存器 */
        SR1_Tmp = I2C_ReadRegister(EEPROM_I2Cx, I2C_Register_SR1);

        /* 发送 EEPROM 地址 + 写方向 */
        I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Transmitter);
    }
    // SR1 位1 ADDR：1 表示地址发送成功，0表示地址发送没有结束
    // 等待地址发送成功
    while (!(I2C_ReadRegister(EEPROM_I2Cx, I2C_Register_SR1) & 0x0002));

    /* 清除 AF 位 */
    I2C_ClearFlag(EEPROM_I2Cx, I2C_FLAG_AF);
    /* 发送停止信号 */
    I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
}

/**
* @brief    在EEPROM的一个写循环中可以写多个字节，但一次写入的字节数
*           不能超过EEPROM页的大小，AT24C02每页有8个字节
* @param
* @param    pBuffer:缓冲区指针
* @param    WriteAddr:写地址
* @param    NumByteToWrite:要写的字节数要求NumByToWrite小于页大小
* @retval   正常返回1，异常返回0
*/
uint8_t I2C_EE_PageWrite(uint8_t* pBuffer, uint8_t WriteAddr, uint8_t NumByteToWrite)
{
    I2CTimeout = I2CT_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(EEPROM_I2Cx, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(4);
    }

    /* 产生I2C起始信号 */
    I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* 检测 EV5 事件并清除标志 */
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(5);
    }

    /* 发送EEPROM设备地址  */
    I2C_Send7bitAddress(EEPROM_I2Cx,EEPROM_ADDRESS,I2C_Direction_Transmitter);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* 检测 EV6 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(6);
    }
    /* 发送要写入的EEPROM内部地址(即EEPROM内部存储器的地址) */
    I2C_SendData(EEPROM_I2Cx, WriteAddr);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* 检测 EV8 事件并清除标志*/
    while (! I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(7);
    }
    /* 循环发送NumByteToWrite个数据 */
    while (NumByteToWrite--)
    {
        /* 发送缓冲区中的数据 */
        I2C_SendData(EEPROM_I2Cx, *pBuffer);
        
        /* 指向缓冲区中的下一个数据 */
        pBuffer++;

        I2CTimeout = I2CT_FLAG_TIMEOUT;

        /* 检测 EV8 事件并清除标志*/
        while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        {
            if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(8);
        }
    }
    return 1;
}

/* AT24C01/02每页有8个字节 */
#define I2C_PageSize    8

/**
* @brief    将缓冲区中的数据写到I2C EEPROM中
* @param
* @arg      pBuffer:缓冲区指针
* @arg      WriteAddr:写地址
* @arg      NumByteToWrite:写的字节数
* @retval   无
*/
void I2C_EE_BufferWrite(u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite)
{
    u8 NumOfPage=0,NumOfSingle=0,Addr =0,count=0,temp =0;

    /*mod运算求余，若writeAddr是I2C_PageSize整数倍，
    运算结果Addr值为0*/
    Addr = WriteAddr % I2C_PageSize;

    /*差count个数据值，刚好可以对齐到页地址*/
    count = I2C_PageSize - Addr;

    /*计算出要写多少整数页*/
    NumOfPage =  NumByteToWrite / I2C_PageSize;

    /*mod运算求余，计算出剩余不满一页的字节数*/
    NumOfSingle = NumByteToWrite % I2C_PageSize;

    // Addr=0,则WriteAddr 刚好按页对齐 aligned
    // 这样就很简单了，直接写就可以，写完整页后
    // 把剩下的不满一页的写完即可
    if (Addr == 0) {
        /* 如果 NumByteToWrite < I2C_PageSize */
        if (NumOfPage == 0) {
            I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
            I2C_EE_WaitEepromStandbyState();
        }
        /* 如果 NumByteToWrite > I2C_PageSize */
        else {
            /*先把整数页都写了*/
            while (NumOfPage--) {
                I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
                I2C_EE_WaitEepromStandbyState();
                WriteAddr +=  I2C_PageSize;
                pBuffer += I2C_PageSize;
            }
            /*若有多余的不满一页的数据，把它写完*/
            if (NumOfSingle!=0) {
                I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
                I2C_EE_WaitEepromStandbyState();
            }
        }
    }
    // 如果 WriteAddr 不是按 I2C_PageSize 对齐
    // 那就算出对齐到页地址还需要多少个数据，然后
    // 先把这几个数据写完，剩下开始的地址就已经对齐
    // 到页地址了，代码重复上面的即可
    else {
        /* 如果 NumByteToWrite < I2C_PageSize */
        if (NumOfPage== 0) {
            /*若NumOfSingle>count，当前面写不完，要写到下一页*/
            if (NumOfSingle > count) {
                // temp的数据要写到写一页
                temp = NumOfSingle - count;

                I2C_EE_PageWrite(pBuffer, WriteAddr, count);
                I2C_EE_WaitEepromStandbyState();
                WriteAddr +=  count;
                pBuffer += count;

                I2C_EE_PageWrite(pBuffer, WriteAddr, temp);
                I2C_EE_WaitEepromStandbyState();
            } else { /*若count比NumOfSingle大*/
                I2C_EE_PageWrite(pBuffer, WriteAddr, NumByteToWrite);
                I2C_EE_WaitEepromStandbyState();
            }
        }
        /* 如果 NumByteToWrite > I2C_PageSize */
        else {
            /*地址不对齐多出的count分开处理，不加入这个运算*/
            NumByteToWrite -= count;
            NumOfPage =  NumByteToWrite / I2C_PageSize;
            NumOfSingle = NumByteToWrite % I2C_PageSize;

            /*先把WriteAddr所在页的剩余字节写了*/
            if (count != 0) {
                I2C_EE_PageWrite(pBuffer, WriteAddr, count);
                I2C_EE_WaitEepromStandbyState();

                /*WriteAddr加上count后，地址就对齐到页了*/
                WriteAddr += count;
                pBuffer += count;
            }
            /*把整数页都写了*/
            while (NumOfPage--) {
                I2C_EE_PageWrite(pBuffer, WriteAddr, I2C_PageSize);
                I2C_EE_WaitEepromStandbyState();
                WriteAddr +=  I2C_PageSize;
                pBuffer += I2C_PageSize;
            }
            /*若有多余的不满一页的数据，把它写完*/
            if (NumOfSingle != 0) {
                I2C_EE_PageWrite(pBuffer, WriteAddr, NumOfSingle);
                I2C_EE_WaitEepromStandbyState();
            }
        }
    }
}

/**
* @brief    从EEPROM里面读取一块数据
* @param    pBuffer:存放从EEPROM读取的数据的缓冲区指针
* @param    ReadAddr:接收数据的EEPROM的地址
* @param    NumByteToRead:要从EEPROM读取的字节数
* @retval   正常返回1，异常返回0
*/
uint8_t I2C_EE_BufferRead(uint8_t* pBuffer, uint8_t ReadAddr, u16 NumByteToRead)
{   
    /* 等待 EEPROM 写入完成 */
    I2C_EE_WaitEepromStandbyState();
    
    I2CTimeout = I2CT_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(EEPROM_I2Cx, I2C_FLAG_BUSY))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(9);
    }

    /* 产生I2C起始信号 */
    I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* 检测 EV5 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(10);
    }

    /* 发送EEPROM设备地址 */
    I2C_Send7bitAddress(EEPROM_I2Cx,EEPROM_ADDRESS,I2C_Direction_Transmitter);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* 检测 EV6 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(11);
    }
    /*通过重新设置PE位清除EV6事件 */
    I2C_Cmd(EEPROM_I2Cx, ENABLE);

    /* 发送要读取的EEPROM内部地址(即EEPROM内部存储器的地址) */
    I2C_SendData(EEPROM_I2Cx, ReadAddr);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* 检测 EV8 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx,I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(12);
    }
    /* 产生第二次I2C起始信号 */
    I2C_GenerateSTART(EEPROM_I2Cx, ENABLE);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* 检测 EV5 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(13);
    }
    /* 发送EEPROM设备地址 */
    I2C_Send7bitAddress(EEPROM_I2Cx, EEPROM_ADDRESS, I2C_Direction_Receiver);

    I2CTimeout = I2CT_FLAG_TIMEOUT;

    /* 检测 EV6 事件并清除标志*/
    while (!I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(14);
    }
    /* 读取NumByteToRead个数据*/
    while (NumByteToRead)
    {
        /*若NumByteToRead=1，表示已经接收到最后一个数据了，
        发送非应答信号，结束传输*/
        if (NumByteToRead == 1)
        {
            /* 发送非应答信号 */
            I2C_AcknowledgeConfig(EEPROM_I2Cx, DISABLE);

            /* 发送停止信号 */
            I2C_GenerateSTOP(EEPROM_I2Cx, ENABLE);
        }

        I2CTimeout = I2CT_LONG_TIMEOUT;
        while (I2C_CheckEvent(EEPROM_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED)==0)
        {
            if ((I2CTimeout--) == 0) return I2C_TIMEOUT_UserCallback(3);
        }
        {
            /*通过I2C，从设备中读取一个字节的数据 */
            *pBuffer = I2C_ReceiveData(EEPROM_I2Cx);

            /* 存储数据的指针指向下一个地址 */
            pBuffer++;

            /* 接收数据自减 */
            NumByteToRead--;
        }
    }

    /* 使能应答，方便下一次I2C传输 */
    I2C_AcknowledgeConfig(EEPROM_I2Cx, ENABLE);
    return 1;
}
