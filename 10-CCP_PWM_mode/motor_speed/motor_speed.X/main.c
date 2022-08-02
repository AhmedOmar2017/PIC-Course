/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 02 ?????, 2022, 06:08 ?
 */



#include <xc.h>
#include <stdint.h>
#include "config.h"

#define _XTAL_FREQ 4000000


#define REV  RB0    //reverse direction button 
#define LVL0 RB1    // 0%   speed button 
#define LVL1 RB2    // 50%  speed button  
#define LVL2 RB3    // 70%  speed button  
#define LVL3 RB4    // 100% speed button 

void PWM1_SET_DUTY(uint16_t);

void main(void) 
{
    // first 5 pins as input 
    TRISB = 0x1F;
    
    // set the output pins
    TRISD0 = 0;
    TRISD1 = 0;
    
    // Initially as counter clock wise
    // for revers set (1, 0)
    RD0 = 0;
    RD1 = 1;
    
    // cofiger the CCP as PWM
    CCP1M3 = 1;
    CCP1M2 = 1;
     
    // the CCP out pin (PWM)
    TRISC2 = 0;  
    
    // set PWM frequncy 2000 Hz
    PR2 = 124;
    
    // set pre-scale for timer2 =4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    
    // start ccp
    TMR2ON = 1;
    
    while(1)
    {
        // reverse direction 
        if(REV)
        {
            RD0 = ~RD0;
            RD1 = ~RD1;
            __delay_ms(500);
        }
        // level 0
        if(LVL0)
        {
            PWM1_SET_DUTY(0);
            __delay_ms(100);        
        }
        // level 1
        if(LVL1)
        {
            PWM1_SET_DUTY(250);
            __delay_ms(100);        
        }
        // level 2
        if(LVL2)
        {
            PWM1_SET_DUTY(375);
            __delay_ms(100);        
        }
        // level 3
        if(LVL3)
        {
            PWM1_SET_DUTY(500);
            __delay_ms(100);        
        }
        __delay_ms(100);
    }
    return;
}

void PWM1_SET_DUTY(uint16_t DC)
{
    if(DC < 1024)
    {
        // put the first two bits in ccp control y and x 
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        // the rest of bits in  ccp low
        CCPR1L = DC >> 2;
    }
}

