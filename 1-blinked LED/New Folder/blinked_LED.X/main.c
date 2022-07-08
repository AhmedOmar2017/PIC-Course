/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 04 ?????, 2022, 01:32 ?
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ  4000000

void main(void) {
    TRISBbits.TRISB0 = 0; // OUTPUT 
    TRISBbits.TRISB1 = 1; // INPUT
    
    PORTBbits.RB0 = 0; // initial value is zero. 
    while (PORTBbits.RB1)
    {
        PORTBbits.RB0 = 1; // LED on 
        __delay_ms(250);
         PORTBbits.RB0 = 0;   // LED off
         __delay_ms(250);
    }
    return;
}
