#include <xc.h>
#include <stdint.h>
#include "config.h"
#define DAC_OUT PORTB
#define _XTAL_FREQ 4000000

uint8_t Sin_table[33]=
{
    0x80,0x98,0xb0,0xc6,0xda,0xea,0xf5,0xfd,0xff,0xfd,
0xf5,0xea,0xda,0xc6,0xb0,0x98,0x80,0x67,0x4f,0x39,
0x25,0x15,0xa,0x2,0x0,0x2,0xa,0x15,0x25,0x39,
0x4f,0x67,0x80  
};
// use potontiometar
#define Task1   0

// out increment voltage with time 
#define Task2   0

// use saw tooth signal Fout = 10 Hz
#define Saw_tooth 0

// use triangle signal Fout = 10 Hz
#define triangle 0


// use sin wave signal Fout = 10 Hz
#define sin_wave 1
        
/*-----------[Prototype ]-------*/

void ADC_INIT();
uint16_t ADC_READ(uint8_t);
/*-----End of prototype--*/


void main(void) {
    #if (Task1 == 1)
        ADC_INIT();
        TRISB = 0x00;
        DAC_OUT = 0x00;
        uint16_t AN0RES;
        while(1)
        {
            AN0RES = ADC_READ(0)>>2;
            DAC_OUT = AN0RES;
            __delay_ms(1);
        }
       
    #endif  
    #if (Task2 == 1)
        TRISB = 0x00;
        PORTB = 0x00;
        __delay_ms(500);
        PORTB = 51;
        __delay_ms(500);
        PORTB = 103;
        __delay_ms(500);
        PORTB = 154;
        __delay_ms(500);
        PORTB = 205;
        __delay_ms(500);
        PORTB = 255;
        __delay_ms(500);
    #endif    
    #if (Saw_tooth == 1)
         TRISB = 0x00;
         uint8_t counter = 0;
         while(1)
         {
            DAC_OUT = counter++;
            __delay_us(390);
         }
    #endif

    #if (triangle == 1)
         TRISB = 0x00;
         DAC_OUT = 0x00;
         uint8_t counter = 0;
         while(1)
         {
             while(counter < 255)
             {
                 DAC_OUT = counter++;
                 __delay_us(196);
             }
             
             while(counter > 0)
             {
                 DAC_OUT = counter--;
                 __delay_us(196);
             }
            
         }
    #endif     
    #if (sin_wave == 1)
          TRISB = 0x00;
         DAC_OUT = 0x00;
         uint8_t i = 0;
         while(1)
         {
             DAC_OUT = Sin_table[i++];
             __delay_us(625);
             if(i == 33)
             {
                 i = 0;
             }
         }
    #endif
    return;
}


/*---------------[ADC IMPELEMENTATION]-----------*/

void ADC_INIT()
{
    ADCON0 = 0x41;          // TURN ON the adc and select AN0 channal = Foc/8
    ADCON1 = 0x80;          // all 8 channals are adc result is right justfied
}



uint16_t ADC_READ(uint8_t ANC)
{
    // CHECK channal validity
    if(ANC< 0 || ANC > 7)   return 0;

    ADCON0  &= 0x11000101;   // CLEAR THE CHANNAL SELECTION  
    ADCON0  |= ANC<<3;       // SELECT THE REQUIRED CHANNAL
    __delay_us(30);         // minimum t = 20 us
    GO_DONE = 1;            // Start adc conversion 

    while(ADCON0bits.GO_DONE);      // polling GO_DONE Bit

    return((ADRESH<<8) + ADRESL);   // return the right justfied 10-bit result
}
