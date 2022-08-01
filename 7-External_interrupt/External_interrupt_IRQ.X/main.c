/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 01 ?????, 2022, 04:52 ?
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

void main(void) {
    // set RC1, RC2 to be output pins 
    TRISC1 = 0;
    TRISC2 = 0;
    
    // initialize pin as low 
    RC1 = 0;
    RC2 = 0;
    
    // set RB0 as input
    TRISB0 = 1;
    
    // set IRQ edge
    INTEDG = 1;
    
    // enable RB0 IRQ
    INTE = 1;
    GIE = 1;
    
    
    while(1)
    {
        // toggle the led for 1second  
        RC2 = 1;
        __delay_ms(1000);
        RC2 = 0;
        __delay_ms(1000);
    }
            
    
    return;
}

// ISR interrupt handler 
void __interrupt() ISR (void)
{
    if(INTF)
    {
        RC1 = ~RC1;
        INTF = 0;
    }
}
