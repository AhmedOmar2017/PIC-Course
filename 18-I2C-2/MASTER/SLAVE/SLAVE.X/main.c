/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 28 ?????, 2022, 12:51 ?
 */


#include <xc.h>
#include "I2C.h"


void main(void) {
    
    TRISD = 0xFF;
    nRBPU = 0;
    I2C_SLAVE_INIT(0x40);   // initiate I2C SLAVE withe address 64= 0x40
    while(1)
    {
    }
    return;
}
