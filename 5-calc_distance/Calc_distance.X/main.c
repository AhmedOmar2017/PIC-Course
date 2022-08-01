/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 01 ?????, 2022, 03:31 ?
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000

float clc_dist(void);

void main(void) {
    // create distance variable 
    unsigned char dist =0;
    
    // set all port B as Output  
    TRISB = 0x00;
    
    // set initial value as low for port B
    PORTB = 0x00;
    
    // set RC2 as output pin (trigger) 
    TRISC2 =0;
    
    // set RC3 as input pin (echo)
    TRISC3 =1;
    // set the pre-scale 1:1
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    
    // select the local clock as TMR clock source
    TMR1CS = 0;
    
    while(1)
    {
        dist  =  clc_dist()/5;
        // LEDs indicator it icreases the number of LEDs every five cm so we divied on 5 
        switch (dist)
        {
            case1: PORTB    = 0x01;
            case2: PORTB    = 0x03;
            case3: PORTB    = 0x07;
            case4: PORTB    = 0x0F;
            default: PORTB  = 0x00;  
        }

    }
    
    return;
}

float clc_dist(void)
{
    float distance =0;
    TMR1 = 0;
    
    //send Trigger pulse to sensor  
    RC2 =1;
    __delay_us(10);
    RC2 =0;
    // wait for the echo pulse from the sensor
    while(!RC3);
    
    // turn on timer mode 
    TMR1ON = 1;
    
    // wait until the pulse ends 
    while (RC3);
    
    // turn off timer 
    TMR1ON = 0;
    
    // calculate the distance using the equation 
    distance = TMR1/58.823;
    return distance;
    
}

