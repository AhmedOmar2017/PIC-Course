/*
 * File:   main.c
 * Author: Prog. & Net. lab
 *
 * Created on August 2, 2022, 9:30 AM
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"

#define _XTAL_FREQ 4000000

#define READ RB0    // read eeprom block
#define W_3  RB1    // write 0x03
#define W_5  RB2    // write 0x05
#define W_7  RB3    // write 0x07

void EEPROM_WR(uint8_t, uint8_t);
uint8_t EEPROM_RD(uint8_t);


void main(void)
{
    TRISB = 0x0F; // FOR PIN AS PIN
    TRISD = 0x00;  // output LEDS
    PORTD = 0x00;  // iNITIALLY OFF
    
    uint8_t Adr  = 0;
    
    while(1)
    {
        if (W_3)
        {
            EEPROM_WR(Adr++, 3);
            __delay_ms(100);
        }
        else if (W_5)
        {
            EEPROM_WR(Adr++, 5);
            __delay_ms(100);
        }
        else if (W_7)
        {
            EEPROM_WR(Adr++, 7);
            __delay_ms(100);
        }
        if(Adr == 3) Adr = 0;
        
        if(READ)
        {
            //read eeprom data to port D 
            for(uint8_t i =0;i < 3; i++)
            {
                PORTD = EEPROM_RD(i);
                __delay_ms(1000);
            }
        }
    }
    return;
}

// write function in EEPROM
void EEPROM_WR(uint8_t ADR, uint8_t DATA)
{
    while(EECON1bits.WR);   // wait until attempt to write is finished
    EEADR = ADR;            // write the address to which we will write our data 
    EEDATA = DATA;          // write the data to saved
    EECON1bits.EEPGD = 0;   // clear to point to EEPROM not the program memory
    EECON1bits.WREN = 1;    // enable the operation 
    INTCONbits.GIE  = 0;    // disable all interrupt until writing data is done 
    EECON2 = 0x55;          // part of write mechanism
    EECON2 = 0xAA;          // part of write mechanism
    EECON1bits.WR = 1;      // part of write mechanism
    INTCONbits.GIE  = 1;    // enable all interrupt until writing data is done
    EECON1bits.WREN = 0;    // disable the operation 
    EECON1bits.WR = 0;      // ready for next writing operation  
}

uint8_t EEPROM_RD(uint8_t ADR)
{
   uint8_t DATA = 0;
   
   EEADR = ADR;            // write the address to which we will write our data 
   EECON1bits.EEPGD = 0;   // clear to point to EEPROM not the program memory
   EECON1bits.RD    = 1;   // start read operation 
   DATA = EEDATA;          // read the data
}



