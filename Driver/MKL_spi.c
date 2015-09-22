/*=============================================================================
#     FileName: MKL_spi.c
#         Desc: SPI接口相关函数
#       Author: Lyn
#        Email: 
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-09-18 14:52:01
#      History:
=============================================================================*/
#include "includes.h"

/* ---------------------------------------------------------------------------*/
/**
 * Description :初始化SPI接口
 *
 * Input    :SPI
 * Input    :bMode
 */
/* ---------------------------------------------------------------------------*/
void SpiInit (){
    /* **
     * 时能时钟
     */
    SIM_SCGC4 |= SIM_SCGC4_SPI1_MASK;  
    /* **
     * SPI System Enable-->SPE,,,SPI系统使能
     */
    SPI1->C1 |= SPI_C1_SPE_MASK ;   
    /* **
     * 设置时钟相位,具体查看SPI协议
     */
    SPI1->C1 &= ~(1 << SPI_C1_CPHA_SHIFT);
    /* **
     * 主机模式
     */
    SPI1->C1 |= SPI_C1_MSTR_MASK;
    /* **
     * 设置1分频,即使用外部设备的时钟,时钟设置参考SystemInit函数.
     */
    SPI1->BR |= SPI_BR_SPPR(0) ; 
}


/* ---------------------------------------------------------------------------*/
/**
 * Description :发送以字节数据
 *
 * Input    :ucdata-->发送数据
 *
 * Output   :是否传输错误
 */
/* ---------------------------------------------------------------------------*/
SPIState Send_Byte (unsigned char ucdata) {
    unsigned char temp;
    unsigned short count=0;
    while(((SPI1_S & SPI_S_SPTEF_MASK) != SPI_S_SPTEF_MASK)&&(count<ErrorCount)){
        count++;
    }
    if(count>=ErrorCount) {
        return SPIError;
    }else {
        SPI1_DL = ucdata;
    }
    count=0;
    while(((SPI1_S & SPI_S_SPRF_MASK) != SPI_S_SPRF_MASK)&&(count<ErrorCount)){
        count++;
    }
    if(count>=ErrorCount){
        return SPIError;
    }else{
        temp = SPI1_DL; 
    }
	return SPISuccess;
}
/* ---------------------------------------------------------------------------*/
/**
 * Description :接受数据
 *
 * Input    :dateRec-->接受到的数据
 *
 * Output   :SPI状态
 */
/* ---------------------------------------------------------------------------*/
SPIState Get_Byte (unsigned char * dateRec) {
    unsigned char temp;
    unsigned short count=0;
    while(((SPI1_S & SPI_S_SPTEF_MASK)!= SPI_S_SPTEF_MASK)&&(count<ErrorCount)){
        count++;
    }
    if(count>=ErrorCount){
        return SPIError;
    }else{
        SPI1_DL = 0xff;
    }
    count=0; 
    while(((SPI1_S & SPI_S_SPRF_MASK)!= SPI_S_SPRF_MASK)&&(count<ErrorCount)){
        count++;
    }
    if(count>=ErrorCount){
        return SPIError;
    }else{
        * dateRec = SPI1_DL;  
    }
	return SPISuccess; 
}

