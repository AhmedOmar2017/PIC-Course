/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 05 ?????, 2022, 08:07 ?
 */


#include <xc.h>
#include "UART.h"

//#define baud_rate 9600

#define UP RB0
#define DOWN RB1
#define SEND RB2



void main(void) {
   // uint8_t baud_rate = 9600;
    init_trans();
    uint8_t data = 0;
    TRISB = 0x07;
    TRISD = 0x00;
    PORTD = 0x00;
    
    while(1)
    {
        if(UP)
        {
            data++;
            __delay_ms(250);
        }
        else if (DOWN)
        {
            data--;
            __delay_ms(250);
        }
        else if(SEND)
        {
            Trans_Fubction(data);
            __delay_ms(250);
        }
        PORTD = data;
    }
    
    return;
}


 
    
