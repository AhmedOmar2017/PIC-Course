/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 27 ?????, 2022, 09:28 ?
 */


#include <xc.h>
#include "I2C.h"


void main(void) {
    
    TRISD = 0x00;
    PORTD = 0x00;
    I2C_SLAVE_INIT(0x40);   // initiate I2C SLAVE withe address 64= 0x40
    while(1)
    {
    }
    return;
}
