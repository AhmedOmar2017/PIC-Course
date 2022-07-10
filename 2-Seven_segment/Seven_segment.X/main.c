/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 10 ?????, 2022, 04:39 ?
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000


void main(void) {
    // put 7-segment into an array
    unsigned char segment_code[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFF, 0xF6};
    unsigned char counter = 0;
    
    TRISB = 0x00;       // PUT ALL PINS IN PORTB AS OUTPUT 
    PORTB = 0x00;       // Initial value is off
    
    
    while(1)
    {
        PORTB = segment_code[counter];
        counter++;
        if (counter == 10) counter = 0;
        __delay_ms(1000);
    }
    
    return;
}
 