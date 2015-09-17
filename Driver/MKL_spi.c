/****************************************Copyright (c)****************************************************
**               Copyright � 2003~2009 Shenzhen uCdragon Technology Co.,Ltd. All Rights Reserved 
**
**                                 http://www.ucdragon.com
**
**      �����������Ƽ����޹�˾���ṩ�����з�������ּ��Э���ͻ����ٲ�Ʒ���з����ȣ��ڷ�����������ṩ
**  ���κγ����ĵ������Խ����������֧�ֵ����Ϻ���Ϣ���������ο����ͻ���Ȩ��ʹ�û����вο��޸ģ�����˾��
**  �ṩ�κε������ԡ��ɿ��Եȱ�֤�����ڿͻ�ʹ�ù��������κ�ԭ����ɵ��ر�ġ�żȻ�Ļ��ӵ���ʧ������˾��
**  �е��κ����Ρ�
**                                                                        �������������Ƽ����޹�˾
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               MKL_spi.c
** Last modified date:     
** Last version:            V1.0
** Descriptions:            spi��غ���
**
** Modified date:      
** Version:            
** Descriptions:       
**
*********************************************************************************************************/
#include "includes.h"


/*********************************************************************************************************
** Function name:           spiInit
** Descriptions:            spi��ʼ��
** input parameters:        SPI�������ַ ��������ģʽ
** output parameters:       none
** Returned value:          none
** Created by:              
** Created date
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void spiInit (SPI_MemMapPtr SPI,BOOLEAN bMode)
{
    SIM_SCGC4 |= SIM_SCGC4_SPI0_MASK;                                   /* ����SPI0                     */
                                                                        /* CPOL = 0, SCK Ϊ����Ч       */
                                                                        /* MSTR = 1, SPI ������ģʽ     */
                                                                        /* LSBF = 0, MSB (λ7)����      */
                                                                        /* SPIE = 0, SPI �жϱ���ֹ     */
                                                                        /* CPHA = 0, SCK��һ��ʱ���ز���*/
    SPI->C1 |= SPI_C1_SPE_MASK ;                                        /* SPIʹ��                      */
    SPI->C1 &= ~(1 << SPI_C1_CPHA_SHIFT);
    if(bMode == Master) {                                               /* ��ģʽ                       */
        SPI->C1 |= SPI_C1_MSTR_MASK;
    } else {                                                            /* ��ģʽ                       */
        SPI->C1 &= ~(1 << SPI_C1_MSTR_SHIFT);
    }
    SPI->BR |= SPI_BR_SPPR(0) ;                                         /* ʱ�ӷ�Ƶ                     */
}

/*********************************************************************************************************
** ��������: Send_Byte
** �������ܣ�SPI����һ���ֽ����� SPI0����
** �������: data
** �������: ��
** �� �� ֵ����
*********************************************************************************************************/
INT8U Send_Byte (INT8U ucdata)
{
    INT8U ucTemp;
    while((SPI0_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);             /* ����ǰҪ���жϼĴ���         */
    SPI0_DL = ucdata;
    
    while((SPI0_S & SPI_S_SPRF_MASK) != SPI_S_SPRF_MASK);               /* ����������Ч                 */
    ucTemp = SPI0_DL;                                                    /* ��ս��ձ�ǼĴ���           */
    ucTemp = ucTemp;
	return ucTemp;
}

/*********************************************************************************************************
** ��������:Get_Byte
** ��������:SPI�ӿڽ���һ���ֽ����� ʹ��SPI0
** �������:��
** �������:��
*********************************************************************************************************/
INT8U Get_Byte (void)
{
    INT8U ucTemp;
    while((SPI0_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);             /* ����ǰҪ���жϼĴ���         */
    SPI0_DL = 0xff;                                                      /* ���Ϳ����ݶ�ȡ����           */

    while((SPI0_S & SPI_S_SPRF_MASK) != SPI_S_SPRF_MASK);               /* ����������Ч                 */
    ucTemp = SPI0_DL;
    return (INT8U)(ucTemp);                                             /* ���ؽ��յ�������             */
}

/*********************************************************************************************************
** Function name:           spiTX
** Descriptions:            spi��ʼ��
** input parameters:        SPI�������ַ ��ѯ��ʽ��������
** output parameters:       none
** Returned value:          none
** Created by:              JiaoLong Liu
** Created date:            2012-12-12
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
*********************************************************************************************************/
void spiTX(SPI_MemMapPtr SPI,INT8U ucData)
{
    while((SPI->S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK);             /* ����ǰҪ���жϼĴ���         */
    SPI->DL = ucData;
}

/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/



