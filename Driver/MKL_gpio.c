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
 * Description :
 */
/* ---------------------------------------------------------------------------*/
void gpioInit(void) 
{
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTD_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTC_MASK;

    PORTB_PCR18 |= (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);   
    PORTB_PCR19 |= (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK);  
    PORTD_PCR1  |= (PORT_PCR_MUX(1) | PORT_PCR_DSE_MASK); 



    PORTB_PCR0  |= PORT_PCR_MUX(1);  
    PORTC_PCR5  |= PORT_PCR_MUX(2); 
    PORTC_PCR6  |= PORT_PCR_MUX(2);
    PORTC_PCR7  |= PORT_PCR_MUX(2);
    FGPIOB_PSOR |= 1<<0;          
    FGPIOB_PDDR |= 1<<0;         

    PORTA_PCR4  |= (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK);
    PORTC_PCR4  |= (PORT_PCR_MUX(1) | PORT_PCR_PE_MASK);

    FGPIOB_PSOR |= 1<<18;            
    FGPIOB_PDDR |= 1<<18;               
    FGPIOB_PSOR |= 1<<19;              
    FGPIOB_PDDR |= 1<<19;             
    FGPIOD_PSOR |= 1<<1;             
    FGPIOD_PDDR |= 1<<1;            

    FGPIOA_PDDR &= ~(1<<4);        
    FGPIOC_PDDR &= ~(1<<4);
}

/*********************************************************************************************************
 ** Function name:           redLedSet
 ** Descriptions:            LED????
 ** input parameters:        True???? False ?ر?
 ** output parameters:       none
 ** Returned value:          none
 ** Created by:             
 ** Created date:            
 **--------------------------------------------------------------------------------------------------------
 ** Modified by:             
 ** Modified date:           
 *********************************************************************************************************/
void Led2Set(BOOLEAN bMode)
{
    if(bMode == True) {
        FGPIOB_PCOR |= 1<<18;                                           /* ????GPIO ?õ?                */
    } else {
        FGPIOB_PSOR |= 1<<18;                                           /* ????GPIO ?ø?                */
    }
}

/*********************************************************************************************************
 ** Function name:           getButton
 ** Descriptions:            ??ȡ????״̬
 ** input parameters:        1ΪK1 2ΪK2 False ?Ͽ?
 ** output parameters:       none
 ** Returned value:          none
 ** Created by:              
 ** Created date:            
 **--------------------------------------------------------------------------------------------------------
 ** Modified by:             
 ** Modified date:           
 *********************************************************************************************************/
BOOLEAN getButton(void)
{
    if((FGPIOA_PDIR & 1<<4) == 1<<4) {
        return False;
    } else {
        return 2;
    }
    if((FGPIOB_PDIR & 1<<0) == 1<<0) {
        return False;
    } else {
        return 1;
    }
}

/*********************************************************************************************************
 ** Function name:           ledSet
 ** Descriptions:            LED????
 ** input parameters:        ??ͬLED????????
 ** output parameters:       none
 ** Returned value:          none
 ** Created by:              
 ** Created date:            
 **--------------------------------------------------------------------------------------------------------
 ** Modified by:             
 ** Modified date:           
 *********************************************************************************************************/
void ledSet(INT8U ucMode)
{
    switch(ucMode) {
        case 0: {                                           // LED 0 on
                    FGPIOB_PCOR |= 1<<18;                           // LED 1 on
                    FGPIOB_PSOR |= 1<<19;                           // LED 2 on
                    FGPIOD_PSOR |= 1<<1;
                    break;
                }
        case 1: {                                           //  LED  
                    FGPIOB_PSOR |= 1<<18;
                    FGPIOB_PCOR |= 1<<19;
                    FGPIOD_PSOR |= 1<<1;
                    break;
                }
        case 2: {
                    FGPIOB_PSOR |= 1<<18;
                    FGPIOB_PSOR |= 1<<19;
                    FGPIOD_PCOR |= 1<<1;
                    break;
                }
        case 3: {
                    FGPIOB_PCOR |= 1<<18;
                    FGPIOB_PCOR |= 1<<19;
                    FGPIOD_PCOR |= 1<<1;
                    break;
                }
        case 4: {
                    FGPIOB_PSOR |= 1<<18;
                    FGPIOB_PSOR |= 1<<19;
                    FGPIOD_PSOR |= 1<<1;
                    break;
                }
        case 5: {
                    FGPIOB_PCOR |= 1<<18;
                    FGPIOB_PSOR |= 1<<19;
                    FGPIOD_PCOR |= 1<<1;
                    break;
                }
        case 6: {
                    FGPIOB_PSOR |= 1<<18;
                    FGPIOB_PCOR |= 1<<19;
                    FGPIOD_PCOR |= 1<<1;
                    break;
                }
        case 7: {
                    FGPIOB_PCOR |= 1<<18;
                    FGPIOB_PCOR |= 1<<19;
                    FGPIOD_PCOR |= 1<<1;
                    break;
                }
    }
}
/*********************************************************************************************************
  END FILE 
 *********************************************************************************************************/



