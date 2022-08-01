/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 01 ?????, 2022, 04:15 ?
 */


#include <xc.h>
#include "config.h"

void main(void) {
    
    // set all port B as Output  
    TRISB = 0x00;
    
    // set initial value as low for port B
    PORTB = 0x00;
    
    //clear the tmr1 
    TMR1 = 0x00;
    
    //select the clock external clock
    TMR1CS = 1;
    
    //turn on T1OSCEN
    T1OSCEN =1;
    
    //Operate in synchronized count mode
    T1SYNC = 0;
    
    // set the pre-scale 1:1
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    
    //turn on timer 1 to enable counter 
    TMR1ON = 1;
    while(1)
    {
        PORTB = TMR1;
    }
    return;
}
