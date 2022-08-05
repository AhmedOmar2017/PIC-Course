/*
 * File:   UART.c
 * Author: Ingenieur
 *
 * Created on 05 ,08, 2022, 07:30 AM
 */


#include <xc.h>
#include "UART.h"

 uint8_t UART_BUFFER = 0;
void Trans_Fubction(uint8_t data)
{
    //set high speed baud rate  
    BRGH = 1;
    
    // from equation of baud rate 9600 
    SPBRG = 25;
    
    //enable the asynchronous serial port
    SYNC = 0;   // disable synchronous 
    SPEN = 1;   // enable serial port
    
    
    /*==================================
     *          set RX/TX TO BE UART 
     ===================================*/
    TRISC6 = 1;
    TRISC7 = 1;
    TXEN   = 1; // enable UART transmission
    
    
    /*=====================================
          function to transmitted  data
     ======================================*/
    while (!TRMT);
    TXREG = data;
}


uint8_t Receive_fuction(void)
{
   
    
    //set high speed baud rate  
    BRGH = 1;
    
    // from equation of baud rate 9600 
    SPBRG = 25;
    
    //enable the asynchronous serial port
    SYNC = 0;   // disable synchronous 
    SPEN = 1;   // enable serial port
    
     /*==================================
     *          set RX/TX TO BE UART 
     ===================================*/
    TRISC6 = 1;
    TRISC7 = 1;
    
    
    /*====================================
     *      enable interrupt receive
     =====================================*/
    RCIE = 1;   // enable UART receiver interrupt
    PEIE = 1;   // enable peripheral interrupt
    GIE = 1;   // enable global interrupt
    
    CREN = 1;   // enable data continous reciption
    
   /* void __interrupt () ISR(void)
    {*/
        if(RCIF == 1)
        {
            RCIF = 0;
            UART_BUFFER =  RCREG;
        }
    /*}
    */
   // UART_BUFFER =  RCREG;
    return UART_BUFFER;
}
void __interrupt () ISR(void)
    {
        if(RCIF == 1)
        {
           // RCIF = 0;
            UART_BUFFER =  RCREG;
        }
    }
