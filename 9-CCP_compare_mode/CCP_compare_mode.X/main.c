/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 02 ?????, 2022, 03:26 ?
 */


#include <xc.h>
#include "cofig.h"
#include <stdint.h>
#include <PIC16F877A.h>


uint8_t x= 0;   //counter for compare event

void main(void) 
{
    // configration the I/O pins 
    TRISC4 = 0;
    RC4 = 0;
    
    // Timer cofig to operate as timer mode 
    TMR1 = 0;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    TMR1CS  = 0;
    TMR1ON  = 1;
    
    // config ccp as compare mode 
    CCPR1 = 50000;  // pre-load 
    
    // ccp in compare mode 
    CCP1M0 = 1;
    CCP1M1 = 1;
    CCP1M2 = 0;       
    CCP1M3 = 1;
    
    //enable ccp interrupt 
    CCP1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    
    while(1)
    {
        
    }
    
    return;
}
void __interrupt () ISR(void)
{
    if(CCP1IF)
    {
        x++;
        if(x == 10)
        {
            // toggle the rc4
            RC4 = ~RC4;
            x = 0;
        }
        //clear the flag
        CCP1IF = 0;
        
    }
}