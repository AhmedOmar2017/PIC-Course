/*
 * File:   main.c
 * Author: Ingenieur
 *
 * Created on 26 ?????, 2022, 12:50 ?
 */


#include <xc.h>
#include "config.h"
#include "LCD.h"

void main(void) {
     LCD_INIT();   // Initialize the Lcd 4-bit interface
     LCD_CLEAR();  // clear lcd
     LCD_SET_CORSER(1, 1);
     LCD_WRITE_STRING("HELLO, WORLD");
     LCD_SET_CORSER(2, 1);
     LCD_WRITE_STRING("AHMED, OAMR");
     while(1)
     {
         for(int i = 0; i < 4; i++)
         {
             __delay_ms(300);
             LCD_SR();     // shift the display to LEFT
         }  
         for(int i = 0; i < 4; i++)
         {
             __delay_ms(300);
             LCD_SL();     // shift the display to LEFT
         }    
          

     }
    return;
}
