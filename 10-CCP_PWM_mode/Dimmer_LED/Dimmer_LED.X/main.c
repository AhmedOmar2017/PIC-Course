/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 02 ?????, 2022, 05:28 ?
 */
/*in this example we control the brightness of LED we assume:
 *  frequancy of pwm  2000Hz  so PR2 = 124;
 *  duty 100% 
 * so pre-scale 4 cause we but the value in 8 bit
 *   */

#include <xc.h>
#include <stdint.h>
#include "config.h"

#define _XTAL_FREQ 4000000

void PWM1_SET_DUTY(uint16_t);


void main(void)
{
    // cofiger the CCP as PWM
    CCP1M3 = 1;
    CCP1M2 = 1;
     
    // the CCP out pin (PWM)
    TRISC2 = 0;  
   
    // set PWM frequncy 
    PR2 = 124;
    
    // set pre-scale for timer2 =4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    
    // start ccp
    TMR2ON = 1;
    
    uint16_t DC =0;
    while(1)
    {
        DC =0;
        // gradually increase LED brightness 
        while(DC < 500)
        {
            PWM1_SET_DUTY(DC);
            DC++;
            __delay_ms(2);
        }
        __delay_ms(100);
        // gradually decrease LED brightness 
        while(DC > 0)
        {
            PWM1_SET_DUTY(DC);
            DC--;
            __delay_ms(2);
        }
        __delay_ms(100);
    }
    return;
}

void PWM1_SET_DUTY(uint16_t DC)
{
    if(DC < 1024)
    {
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
}
