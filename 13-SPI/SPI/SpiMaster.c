/* file include example how to use 
 * SPI as master 
 * auther: Ahmed omar 
*/

#include <xc.h>
#include <stdint.h>
#include "CONFIG.h"

#define _XTAL_FREQ 4000000

#define UP   RB0
#define DOWN RB1
#define Send RB2

/*================================================
 * Function decliration 
 *================================================*/
void SPI_MASTER_INIT();
void SPI_MASTER_WRITE(uint8_t);
/*-------------------------------------------------*/




/*================================================
 * Main routine 
 *================================================*/
 void main ()
 {
    //[coifugration ]
    SPI_MASTER_INIT();
    uint8_t Data = 0;
    TRISB = 0x07;      // RB0, RB1, RB2 are input pins 
    TRISD = 0x00;      // Output port
    PORTD = 0x00;      // initially Off
    /*------ End configration-------------------------*/

    while(1)
    {
        // increament Data
        if(UP)
        {
            Data++;
            _Delay_ms(250);
        }
        // decrement data
        else if (DOWN)
        {
             Data--;
            _Delay_ms(250);
        }
        // send data through spi
        else if (Send)
        {
            SPI_MASTER_WRITE(Data);
            _Delay_ms(250);
        }
        PORTD = data;
    } 
    return;     
 }

/*===================================================
 * Prortotype function of initializing of SPI master 
 *===================================================*/
 void SPI_MASTER_INIT()
 {
    // set SPI mode to master + set Sck rate fosc/4
    SSPM0 = 0;
    SSPM1 = 0;
    SSPM2 = 0;
    SSPM3 = 0;

    //Enable the syncronous serial port
    SSPEN = 1;

    // Configure the clock polarity and phase 
    SKP = 0;
    CKE = 0;

    // Configure the sampling time 
    SMP = 0;

    // Configure the I/O pins for SPI master mode 
    TRISCS5 = 0;    // SDO OUTPUT
    TRISCS4 = 1;    // SDI INPUT
    TRISCS3 = 0;    // SCK OUTPUT

    /*-----------------------------------------------------
     * If the interrupt are needed uncomment the line below
     *-----------------------------------------------------*/
     // SSPIE = 1;
     // PEIE  = 1;
     // GIE   = 1;
     /*--------------------End of SPI interrupt---------------*/

 }

 /*===================================================
 * Prortotype function of writing of SPI master 
 *===================================================*/
void SPI_MASTER_WRITE(uint8_t data)
{
    SSPBUF = data;  // transfer the data to buffer register

}