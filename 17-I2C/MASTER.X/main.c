/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 27 ?????, 2022, 05:59 ?
 */


#include <xc.h>
#include "I2C.h"

void main(void) {
    
    TRISB = 0xFF;
    TRISD = 0x00;
    PORTD = 0x00;
    unsigned char i = 1;
    I2C_MASTER_INIT();
    
    
    while(1)
    {
        I2C_start();
        I2C_WRITE(0x40);
        I2C_WRITE(i++);
        I2C_stop();
        __delay_ms(500);
        RD3 = ~RD3;
    }
    
    return;
}
