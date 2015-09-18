/*=============================================================================
#     FileName: MKL_gpio.c
#         Desc: GPIO Driver
#       Author: Lyn
#        Email: 
#     HomePage: 
#      Version: 0.0.1
#   LastChange: 2015-09-17 14:09:37
#      History:
=============================================================================*/
#include "includes.h"
/* ---------------------------------------------------------------------------*/
/**
 * Description : 对嵌入式系统的引脚进行初始化
 */
/* ---------------------------------------------------------------------------*/
void GpioInit(void){
    /* **
     *IO口时钟开启,端口A的时钟在SystemInit中已经开启.
     */
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK;

    /* **
     * SPI引脚初始化,用于DW1000.
     */
    PORTD_PCR5  |= PORT_PCR_MUX(2); //SCK
    PORTD_PCR6  |= PORT_PCR_MUX(2); //MISO
    PORTD_PCR7  |= PORT_PCR_MUX(2); //MOSI

    PORTD_PCR4  |= PORT_PCR_MUX(1); //CS,设置为GPIO功能
    FGPIOD_PSOR |= 1<<4;            //引脚设为高电平
    FGPIOD_PDDR |= 1<<4;            //引脚输出
    /* **
     * DW1000相关引脚初始化
     */
    PORTC_PCR7  |= PORT_PCR_MUX(1); //WakeUp,设置为GPIO功能
    FGPIOC_PCOR |= 1<<7;            //引脚设为低电平
    FGPIOC_PDDR |= 1<<7;            //引脚输出

    PORTD_PCR0  |= PORT_PCR_MUX(1); //Reset,设置为GPIO功能
    FGPIOD_PSOR |= 1<<0;            //引脚设为高电平
    FGPIOD_PDDR |= 1<<0;            //引脚输出

    PORTD_PCR1  |= PORT_PCR_MUX(1); //Power,设置为GPIO功能,高电平使能
    FGPIOD_PCOR |= 1<<1;            //引脚设为低电平
    FGPIOD_PDDR |= 1<<1;            //引脚输出


    PORTA_PCR4  |= PORT_PCR_IRQC(9)|PORT_PCR_MUX(1); //Interrupt,上升沿中断,设置为GPIO功能
    NVIC_EnableIRQ(PORTA_IRQn);     //使能中断

    /* **
     * GPS--串口引脚初始化
     */
    PORTE_PCR16 = PORT_PCR_MUX(0x3);  /* UART0_TXD */
    PORTE_PCR17 = PORT_PCR_MUX(0x3);  /* UART0_RXD */
    /* **
     * GPS相关引脚初始化
     */
    PORTD_PCR2  |= PORT_PCR_MUX(1); //Power,设置为GPIO功能,高电平使能
    FGPIOD_PCOR |= 1<<2;            //引脚设为低电平
    FGPIOD_PDDR |= 1<<2;            //引脚输出

    PORTE_PCR18  |= PORT_PCR_MUX(1); //Reset,设置为GPIO功能,高电平使能
    FGPIOE_PCOR |= 1<<18;            //引脚设为低电平
    FGPIOE_PDDR |= 1<<18;            //引脚输出
    /* **
     * GPRS--串口初始化
     */
    PORTE_PCR20 = PORT_PCR_MUX(0x4);  /* UART0_TXD */
    PORTE_PCR21 = PORT_PCR_MUX(0x4);  /* UART0_RXD */
    /* **
     * GPRS相关引脚初始化
     */
    PORTD_PCR3  |= PORT_PCR_MUX(1); //Power,设置为GPIO功能,高电平使能
    FGPIOD_PCOR |= 1<<3;            //引脚设为低电平
    FGPIOD_PDDR |= 1<<3;            //引脚输出

    PORTE_PCR19  |= PORT_PCR_MUX(1); //唤醒,设置为GPIO功能,低电平有效
    FGPIOE_PSOR |= 1<<19;            //引脚设为高电平
    FGPIOE_PDDR |= 1<<19;            //引脚输出

    /* **
     * 电压检测引脚初始化
     */
    PORTC_PCR1  |= PORT_PCR_MUX(1); //使能电压检测,设置为GPIO功能,高电平使能
    FGPIOC_PCOR |= 1<<1;            //引脚设为低电平
    FGPIOC_PDDR |= 1<<1;            //引脚输出

    PORTC_PCR2  |= PORT_PCR_MUX(0); //引脚默认即为ADC模式.
    /* **
     * 检测按键
     */
    PORTC_PCR4  |= PORT_PCR_IRQC(9)|PORT_PCR_MUX(1); //Interrupt,上升沿中断,设置为GPIO功能
    PORTC_PCR5  |= PORT_PCR_IRQC(9)|PORT_PCR_MUX(1); //Interrupt,上升沿中断,设置为GPIO功能
    NVIC_EnableIRQ(PORTC_PORTD_IRQn);     //使能中断

    /* **
     * 指示灯
     */
    PORTB_PCR0  |= PORT_PCR_MUX(1); //指示灯,设置为GPIO功能
    FGPIOB_PSOR |= 1<<0;            //引脚设为高电平
    FGPIOB_PDDR |= 1<<0;            //引脚输出

    /* **
     * 检测腕带是否被破坏
     */
    PORTA_PCR1  |= PORT_PCR_IRQC(10)|PORT_PCR_MUX(1); //Interrupt,下降沿中断,设置为GPIO功能
    PORTA_PCR2  |= PORT_PCR_IRQC(10)|PORT_PCR_MUX(1); //Interrupt,下降沿中断,设置为GPIO功能
}



/* ---------------------------------------------------------------------------*/
/**
 * Description :指示灯闪烁
 */
/* ---------------------------------------------------------------------------*/
void LedSpark(){

    /* **
     * 为1则引脚高低电平反转
     */
    FGPIOB_PTOR=1<<0;
    
    /*static unsigned char flag=0;*/
    /*if(flag==0){*/
        /*flag=1;*/
        /*FGPIOB_PCOR |= 1<<0;  //引脚设为低电平,LED变亮*/
    /*}else{*/
        /*flag=0;*/
        /*FGPIOB_PSOR |= 1<<0;  //引脚设为高电平*/
    /*}*/
}



