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
 * Description :GPRS���ڳ�ʼ��,ʹ��UART0,Ŀǰ��֧��10λ.
 *
 * Input    :ulBaudRate------->������
 * Input    :ucParityEnable--->У��
 * Input    :ucParityType----->��żУ��
 * Input    :ucDataLength----->���ݳ���
 * Input    :ucStopBit-------->ֹͣλ
 */
/* ---------------------------------------------------------------------------*/
void  GPRS_Uart_Init (unsigned long  ulBaudRate, 
        unsigned char   ucParityEnable,
        unsigned char   ucParityType,
        unsigned char   ucDataLength, 
        unsigned char   ucStopBit);


/* ---------------------------------------------------------------------------*/
/**
 * Description :GRS���ڳ�ʼ��,ʹ��UART2.
 *
 * Input    :ulBaudRate------->������
 * Input    :ucParityEnable--->У��
 * Input    :ucParityType----->��żУ��
 * Input    :ucDataLength----->���ݳ���
 * Input    :ucStopBit-------->ֹͣλ
 */
/* ---------------------------------------------------------------------------*/
void  GPS_Uart_Init (unsigned long  ulBaudRate, 
        unsigned char   ucParityEnable,
        unsigned char   ucParityType,
        unsigned char   ucDataLength, 
        unsigned char   ucStopBit); 



/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS����һ�ֽ�����
 *
 * Output   :
 */
/* ---------------------------------------------------------------------------*/
unsigned char  GPRS_Get_Char (void); 

/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS����һ�ֽ�����
 *
 * Output   :
 */
/* ---------------------------------------------------------------------------*/
unsigned char  GPS_Get_Char (void); 
/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS����һ�ֽ�
 *
 * Input    :ucData
 */
/* ---------------------------------------------------------------------------*/
void  GPRS_Send_Char (unsigned char  ucData);



/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS����һ�ֽ�
 *
 * Input    :ucData
 */
/* ---------------------------------------------------------------------------*/
void  GPS_Send_Char (unsigned char  ucData);

/* ---------------------------------------------------------------------------*/
/**
 * Description :GPRS�����ַ���
 *
 * Input    :pucBuf
 */
/* ---------------------------------------------------------------------------*/
void  GPRS_Send_String (unsigned char  *pucBuf);


/* ---------------------------------------------------------------------------*/
/**
 * Description :GPS�����ַ���
 *
 * Input    :pucBuf
 */
/* ---------------------------------------------------------------------------*/
void  GPS_Send_String (unsigned char  *pucBuf);





#endif


