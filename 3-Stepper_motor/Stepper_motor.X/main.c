/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 10 ?????, 2022, 05:42 ?
 */


#include <xc.h>
#include "config.h"

#define _XTAL_FREQ 4000000


void main(void) {
    
    // create bit shifting variable
    unsigned char i = 0; 
    
    // set portb  5 pins  to be output 
    TRISB = 0x00;
    
    // Initial pin low output 
    PORTB = 0x00;
    
    // Create symbol main routine
    while(1)
    {
        // turn in one side 
        for(uint8_t j = 0; j <= 48; j++)
        {
            PORTB = (1 << i);
            i++;
            __delay_ms(100);
            if(i == 4) i = 0;
            
        }
        // wait for a second 
        __delay_ms(1000);
        // turn in anther side 
        for(uint8_t j = 0, i = 0; j <= 48; j++)
        {
            PORTB = (8>>i);
            i++;
            __delay_ms(100);
            if(i == 4) i = 0;
            
        }
        // wait for a second 
        __delay_ms(1000);
    }
    return;
}
