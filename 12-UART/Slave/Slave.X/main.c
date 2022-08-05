/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 05 ?????, 2022, 08:48 ?
 */


#include <xc.h>
#include "UART.h"

void main(void) 
{
   // uint8_t baud_rate = 9600;
    TRISB = 0x00;
    PORTB = 0x00;
    //slave_init (9600);
    while(1)
    {
        PORTB = Receive_fuction();
    }
    return;
}
