/*
 * File:   main.c
 * Author: Prog. & Net. lab
 *
 * Created on August 1, 2022, 10:04 AM
 */


#include <xc.h>
#include"config.h"



void main(void) {
    
    TRISB = 0x00;
    PORTB = 0x00;
    
    TRISD = 0x00;
    PORTD = 0x00;
    
    TMR1 = 0;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    TMR1CS = 1;
    T1OSCEN = 1;
    T1SYNC = 0;
    TMR1ON = 1;
    
    CCP1M0 = 1;
    CCP1M1 = 0;
    CCP1M2 = 1;
    CCP1M3 = 0;
    
    CCP1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    while(1)
    {
        PORTD = TMR1;
    }
    return;
}


void __interrupt()ISR(void)
{
    if(CCP1IF)
    {
        PORTB = CCPR1;
        CCP1IF = 0;
    }
}