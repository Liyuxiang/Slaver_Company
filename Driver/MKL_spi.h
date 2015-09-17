/*********************************************************************************************************/
#ifndef __ZMD_UID_MKL_H
#define __ZMD_UID_MKL_H
#include "includes.h"

#ifdef __cplusplus
extern "C" {
#endif
/*********************************************************************************************************
  �궨��
*********************************************************************************************************/
#define Master 0
#define Slave  1
/*********************************************************************************************************
  �������� 
*********************************************************************************************************/  
extern void spiInit(SPI_MemMapPtr SPI,BOOLEAN bMode);
extern void spiTX(SPI_MemMapPtr SPI,INT8U ucData);
    
extern INT8U Send_Byte (INT8U ucdata);
extern INT8U Get_Byte (void);
#ifdef __cplusplus
}
#endif


#endif


/*********************************************************************************************************
  END FILE 
*********************************************************************************************************/  