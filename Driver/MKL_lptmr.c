/*=============================================================================
#     FileName: MKL_lptmr.c
#         Desc: 低功耗时钟,使用时钟来实现低功耗的控制.
#       Author: Lyn
#        Email: 
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-09-18 17:44:35
#      History:
=============================================================================*/
#include "includes.h"

/* ---------------------------------------------------------------------------*/
/**
 * Description :低功耗定时器初始化,使能中断
 */
/* ---------------------------------------------------------------------------*/
void Lptmr_Init(){
    /* **
     * 开启时钟
     */
    SIM_SCGC5 |= SIM_SCGC5_LPTMR_MASK;    
    /* **
     * 清除标志位,开始中断
     */
    LPTMR0_CSR |= LPTMR_CSR_TCF_MASK | LPTMR_CSR_TIE_MASK; 
    /* **
     * 选择1KHZ时钟源,其实在systemInit中已经使用.
     */
    LPTMR0_PSR |= LPTMR_PSR_PCS(1);     
    /* **
     * 多久中断一次,二分频,每个数字2ms
     */
    LPTMR0_CMR = 500;
    /* **
     * 定时器使能
     */
    LPTMR0_CSR |= LPTMR_CSR_TEN_MASK;     

    /* **
     * 中断
     */
     NVIC_EnableIRQ(LPTimer_IRQn);                
     /* **
      * 中断优先级
      */
     NVIC_SetPriority(LPTimer_IRQn,3);            
}




/* ---------------------------------------------------------------------------*/
/**
 * Description :中断
 */
/* ---------------------------------------------------------------------------*/
void LPTimer_IRQHandler(void) {
	 LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   
	 //FGPIOD_PTOR=1<<1;
}
