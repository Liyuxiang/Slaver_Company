/*=============================================================================
#     FileName: main.c
#         Desc: 
#       Author: Lyn
#        Email: 
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-09-16 14:40:18
#      History:
=============================================================================*/
#include "includes.h"
#include "MKL_smc.h"
int main(void){
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;
    PORTD_PCR1  |= PORT_PCR_MUX(1); //指示灯,设置为GPIO功能
    FGPIOD_PCOR |= 1<<1;            //引脚设为高电平
    FGPIOD_PDDR |= 1<<1;            //引脚输出
    enter_vlpr();
    Lptmr_Init();
	while(1){
        sleep();
        FGPIOD_PTOR=1<<1;
	}
    return 0;
}
