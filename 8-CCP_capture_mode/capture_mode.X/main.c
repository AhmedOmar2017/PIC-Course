/*
 * File:   main.c
 * Author: Prog. & Net. lab
 *
 * Created on August 1, 2022, 10:04 AM
 */


#include <xc.h>
#include"config.h"



void main(void) {
    // set the port B as output for capture operation  
    TRISB = 0x00;
    PORTB = 0x00;   //initial value is zero
    
    // set the port D as output for Timer operation  
    TRISD = 0x00;
    PORTD = 0x00;   //initial value is zero
    
    /* configration of timer as a counter  */
    TMR1 = 0;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    TMR1CS = 1;
    T1OSCEN = 1;
    T1SYNC = 0;
    TMR1ON = 1;
    
    /* configration  ccp1 to operaten as a capture mode every rising edge */
    CCP1M0 = 1;
    CCP1M1 = 0;
    CCP1M2 = 1;
    CCP1M3 = 0;
    
    /* enable ccp1 interrupt */
    CCP1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    
    while(1)
    {
        // print out value of timer 1
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