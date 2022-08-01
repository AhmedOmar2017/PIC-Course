/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 01 ?????, 2022, 01:26 ?
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000


//create a global variable 
unsigned char count = 0;

void main(void) 
{
    // set RB0 output
    TRISB0 = 0;
    // set the initial value zero
    RB0 = 0;
    // Enable TMR1 interrupt
    TMR1IE  = 1;
    PEIE    = 1;
    GIE     = 1;
    /*Configration timer module to operate  Timer mode */ 
   
    // set count from zero
    TMR1 = 0;
    // set count from 15536
    TMR1 = 15536;
    // select the local clock as TMR clock source
    TMR1CS = 0;
    // set the pre-scale 1:1
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    // Turn on TMR1 module 
    TMR1ON = 1;
    // write the system's main routine 
    while(1)
    {
    }
    return;
}

void __interrupt() ISR (void)
{
    if(TMR1IF)
    {
        // pre-load timer to accurate the value second  
        TMR1 = 15536;
        count++; 
        if (count == 20)
        {
            RB0 = ~RB0;
            count = 0;
        }
        TMR1IF = 0;
    }
}