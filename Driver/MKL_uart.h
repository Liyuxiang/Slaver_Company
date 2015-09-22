/*=============================================================================
#     FileName: MKL_uart.h
#         Desc: 
#       Author: Lyn
#        Email: 
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-09-18 17:26:56
#      History:
=============================================================================*/
#ifndef __UART_MKL_H
#define __UART_MKL_H

/* **
 * 
 */
#define UART_TX_ENABLE          1
#define UART_TX_DISABLE         0

#define UART_RX_ENABLE          1
#define UART_RX_DISABLE         0
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
        unsigned char   ucStopBit);


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
        unsigned char   ucStopBit); 



/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS接收一字节数据
 *
 * Output   :
 */
/* ---------------------------------------------------------------------------*/
unsigned char  GPRS_Get_Char (void); 

/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS接收一字节数据
 *
 * Output   :
 */
/* ---------------------------------------------------------------------------*/
unsigned char  GPS_Get_Char (void); 
/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS发送一字节
 *
 * Input    :ucData
 */
/* ---------------------------------------------------------------------------*/
void  GPRS_Send_Char (unsigned char  ucData);



/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS发送一字节
 *
 * Input    :ucData
 */
/* ---------------------------------------------------------------------------*/
void  GPS_Send_Char (unsigned char  ucData);

/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS发送字符串
 *
 * Input    :pucBuf
 */
/* ---------------------------------------------------------------------------*/
void  GPRS_Send_String (unsigned char  *pucBuf);


/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS发送字符串
 *
 * Input    :pucBuf
 */
/* ---------------------------------------------------------------------------*/
void  GPS_Send_String (unsigned char  *pucBuf);





#endif


