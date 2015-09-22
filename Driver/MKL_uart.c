/*=============================================================================
#     FileName: MKL_uart.c
#         Desc: 串口底层函数
#       Author: Lyn
#        Email: 
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-09-18 15:43:20
#      History:
=============================================================================*/
#include "includes.h"
#include "MKL_uart.h"
extern unsigned long SystemBusClock;
/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS串口初始化,使用UART0,目前不支持10位.
 *
 * Input    :ulBaudRate------->波特率
 * Input    :ucParityEnable--->校验
 * Input    :ucParityType----->奇偶校验
 * Input    :ucDataLength----->数据长度
 * Input    :ucStopBit-------->停止位
 */
/* ---------------------------------------------------------------------------*/
void  GPRS_Uart_Init (unsigned long  ulBaudRate, 
        unsigned char   ucParityEnable,
        unsigned char   ucParityType,
        unsigned char   ucDataLength, 
        unsigned char   ucStopBit) {
    register unsigned short usBaudRate  = 0;  

    SIM_SOPT2 |= SIM_SOPT2_UART0SRC(3);   
    SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;   
    /* **
     * 失能UART0的发送接受功能.
     */
    UART0_C2_REG(UART0)&= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK);

    /* **
     * 先清除寄存器相关位
     */
    UART0_C1_REG(UART0) &= ~(UART0_C1_M_MASK |
            UART0_C1_PT_MASK |              
            UART0_C1_PE_MASK);             
    UART0_C4_REG(UART0) &= ~UART0_C4_M10_MASK; 
    /* **
     * 设置发送位长
     * 校验使能
     * 奇偶校验
     */
    UART0_C1_REG(UART0) |= ((ucDataLength - 8UL) << UART0_C1_M_SHIFT)|
        (ucParityEnable << UART0_C1_PE_SHIFT)|
        (ucParityType << UART0_C1_PT_SHIFT);                

    /* **
     * 设置波特率
     */
	UART0_C4_REG(UART0) &= ~ UART0_C4_OSR_MASK;
	UART0_C4_REG(UART0) |=  UART0_C4_OSR(3);//----->对应下面的4
    usBaudRate = SystemBusClock/(ulBaudRate * 4);
    UART0_BDH_REG(UART0)  = (usBaudRate & 0x1F00) >> 8;  
    UART0_BDL_REG(UART0)  = (unsigned char)(usBaudRate & UART0_BDL_SBR_MASK);
    /* **
     * 停止位
     */
    UART0_BDH_REG(UART0) &= ~UART0_BDH_SBNS_MASK;   
    UART0_BDH_REG(UART0) |= (ucStopBit - 1) << UART0_BDH_SBNS_SHIFT;
    /* **
     * 中断
     */
    UART0_C2_REG(UART0)  &= ~(UART0_C2_TIE_MASK | UART0_C2_TCIE_MASK |       
            UART0_C2_RIE_MASK | UART0_C2_ILIE_MASK); 

    /* **
     * 等待接收寄存器和数据寄存器为空
     */
    while ((UART0_S1_REG(UART0) & UART0_S1_RDRF_MASK) &&
            (UART0_D_REG(UART0))); 
    /* **
     * 使能UART发送接收
     */
    UART_C2_REG(UART0) |= (UART_TX_ENABLE << UART_C2_TE_SHIFT)|
        (UART_RX_ENABLE << UART_C2_RE_SHIFT);

    /* **
     * 接收中断使能
     */
    UART0_C2_REG(UART0) |= UART0_C2_RIE_MASK;
    NVIC_EnableIRQ(UART0_IRQn);
    NVIC_SetPriority(UART0_IRQn,3); 

}


/* ---------------------------------------------------------------------------*/
/**
 * Description :GRS串口初始化,使用UART2.
 *
 * Input    :ulBaudRate------->波特率
 * Input    :ucParityEnable--->校验
 * Input    :ucParityType----->奇偶校验
 * Input    :ucDataLength----->数据长度
 * Input    :ucStopBit-------->停止位
 */
/* ---------------------------------------------------------------------------*/
void  GPS_Uart_Init (unsigned long  ulBaudRate, 
        unsigned char   ucParityEnable,
        unsigned char   ucParityType,
        unsigned char   ucDataLength, 
        unsigned char   ucStopBit) {
    register unsigned short usBaudRate  = 0;  

    SIM_SCGC4 |= SIM_SCGC4_UART2_MASK;
    /* **
     * 使能发送接收
     */
    UART_C2_REG(UART2) &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

    /* **
     * 设置数据长度,奇偶校验
     */
    UART_C1_REG(UART2) &= ~(UART_C1_M_MASK | 
            UART_C1_PT_MASK |
            UART_C1_PE_MASK);
    UART_C1_REG(UART2) |= ((ucDataLength - 8UL) << UART_C1_M_SHIFT)|
        (ucParityEnable << UART_C1_PE_SHIFT)|
        (ucParityType << UART_C1_PT_SHIFT);                
    /* **
     * 设置波特率
     */
    usBaudRate = SystemBusClock/(ulBaudRate * 16);    
    UART_BDH_REG(UART2) = (usBaudRate & 0x1F00) >> 8;  
    UART_BDL_REG(UART2) = (unsigned char)(usBaudRate & UART_BDL_SBR_MASK);
    /* **
     * 设置停止位
     */
    UART_BDH_REG(UART2) &= ~UART_BDH_SBNS_MASK; 
    UART_BDH_REG(UART2) |= (ucStopBit - 1) << UART_BDH_SBNS_SHIFT;
    /* **
     * 开始设置中断
     */
    UART_C2_REG(UART2) &= ~(UART_C2_TIE_MASK | UART_C2_TCIE_MASK| 
            UART_C2_RIE_MASK | UART_C2_ILIE_MASK);  

    while ((UART_S1_REG(UART2) & UART_S1_RDRF_MASK) &&
            (UART_D_REG(UART2)));  
    UART_C2_REG(UART2) |= UART_C2_RIE_MASK;
    NVIC_EnableIRQ(UART2_IRQn);
    NVIC_SetPriority(UART2_IRQn,3);    

}



/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS接收一字节数据
 *
 * Output   :
 */
/* ---------------------------------------------------------------------------*/
unsigned char  GPRS_Get_Char (void) {
    while (!(UART0_S1_REG(UART0) & UART0_S1_RDRF_MASK)); 
    return UART0_D_REG(UART0);
}

/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS接收一字节数据
 *
 * Output   :
 */
/* ---------------------------------------------------------------------------*/
unsigned char  GPS_Get_Char (void) {
    while (!(UART_S1_REG(UART2) & UART_S1_RDRF_MASK));   
    return UART_D_REG(UART2);    
}


/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS发送一字节
 *
 * Input    :ucData
 */
/* ---------------------------------------------------------------------------*/
void  GPRS_Send_Char (unsigned char  ucData) {
    while (!((UART0_S1_REG(UART0) & UART0_S1_TDRE_MASK))); 
    UART0_D_REG(UART0) = ucData;   
}



/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS发送一字节
 *
 * Input    :ucData
 */
/* ---------------------------------------------------------------------------*/
void  GPS_Send_Char (unsigned char  ucData) {
    while (!((UART_S1_REG((UART2)) & UART_S1_TDRE_MASK))); 
    UART_D_REG((UART2)) = ucData;  
}


/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS发送字符串
 *
 * Input    :pucBuf
 */
/* ---------------------------------------------------------------------------*/
void  GPRS_Send_String (unsigned char  *pucBuf) {
    while (*pucBuf != '\0') { 
        GPRS_Send_Char(*pucBuf++);
    }    
}


/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS发送字符串
 *
 * Input    :pucBuf
 */
/* ---------------------------------------------------------------------------*/
void  GPS_Send_String (unsigned char  *pucBuf) {
    while (*pucBuf != '\0') { 
        GPS_Send_Char(*pucBuf++);
    }    
}


/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS中断
 */
/* ---------------------------------------------------------------------------*/
void  UART0_IRQHandler (void) {     
    UART0_MemMapPtr uartPtr = UART0_BASE_PTR;     
    while (UART0_S1_REG(uartPtr) & UART0_S1_RDRF_MASK) {   
        //     while(!UART0_D_REG(uartPtr));           
    }   
}


/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS中断
 */
/* ---------------------------------------------------------------------------*/
void  UART2_IRQHandler (void) {
    UART_MemMapPtr uartPtr = UART2_BASE_PTR;  
    while (UART_S1_REG(uartPtr) & UART_S1_RDRF_MASK){    
        while (!UART_D_REG(uartPtr));                  
    }   
}

