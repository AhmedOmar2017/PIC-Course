#include <xc.h>
#include <stdint.h>
#include "config.h"

#define _XTAL_FREQ 4000000



/*-----------[Prototype ]-------*/
void PWM1_INIT();
void PWM1_SET_DUTY(uint16_t);
void ADC_INIT();
uint16_t ADC_READ(uint8_t);
/*-----End of prototype--*/

/*-------------main rotiune ---------------*/
int main(void)
{
    PWM1_INIT();
    ADC_INIT();

    while(1)
    {
        // set PWM duty cycle to AN0_result
        PWM1_SET_DUTY(ADC_READ(0));
        __delay_ms(1);
    }
   
}
/*--------------End of main-------------------*/


/*-------------------[PWM IMPELEMENTATION]--------------------*/
void PWM1_INIT()
{
    // CONFIGERATION
    CCP1M3 = 1;
    CCP1M2 = 1;
    TRISC2 = 0;     // output pin 


    // set frequancy 1kHz for PWM
    PR2 = 255;

    // Set p5 for timer 2 (1:4 ratio)
    T2CKPS0 = 1;
    T2CKPS1 = 0;

    // START CCP1 PWM
    TMR2ON = 1;
 
}



void PWM1_SET_DUTY(uint16_t DC)
{
    // CHEACK THE DC value if it with in 10 bit range
    if (DC < 1024)
    {
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
}
/*-------------End of PWM ---------------------------*/

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

