/*
 * File:   LCD.c
 * Author: Ingenieur
 *
 * Created on 26 ?????, 2022, 12:58 ?
 */


#include <xc.h>
#include "config.h"
#include "LCD.h"


// send 4-BIT command to LCD
void LCD_DATA(unsigned char Data)
{
    if (Data & 1) D4 = 1;
    else D4 = 0;
    if (Data & 2) D5 = 1;
    else D5 = 0;
    if (Data & 4) D6 = 1;
    else D6 = 0;
    if (Data & 8) D7 = 1;
    else D7 = 0;      
}



// send command to LCD
void LCD_CMD(unsigned char CMD)
{
    RS = 0;     // select command register
    LCD_DATA(CMD);      // move the command data to LCD
    EN = 1;             // Enable the clock signal
    __delay_us(LCD_EN_DELAY);   
    EN = 0;
}


// Initialize the Lcd 4-bit interface
void LCD_INIT()
{
    LCD_DATA_PORT_D = 0x00;
    LCD_RS_D = 0;
    LCD_EN_D = 0;
    LCD_DATA(0x00);
    __delay_ms(30);
    __delay_us(LCD_EN_DELAY);
    LCD_CMD(0x03);
    __delay_ms(5);
    LCD_CMD(0x03);
    __delay_us(150);
    LCD_CMD(0x03);
    LCD_CMD(0x02);
    LCD_CMD(0x02);
    LCD_CMD(0x08);
    LCD_CMD(0x00);
    LCD_CMD(0x0C);
    LCD_CMD(0x00);
    LCD_CMD(0x06);
}

// write character to LCD
void LCD_WRITE_CHAR(char data)
{
    char low4, high4;
    low4 = data & 0x0F;
    high4 = data & 0xF0;
    RS = 1;
    LCD_DATA(high4>>4);
    EN = 1;
    __delay_us(LCD_EN_DELAY);
    EN = 0;
    __delay_us(LCD_EN_DELAY);
    LCD_DATA(low4);
     EN = 1;
    __delay_us(LCD_EN_DELAY);
    EN = 0;
    __delay_us(LCD_EN_DELAY);
}

// write string to LCD
void LCD_WRITE_STRING(char* str)
{
    int i;
    for(i = 0;str[i] != '\0';i++)
    {
        LCD_WRITE_CHAR(str[i]);
    }
}


// clear LCD
void LCD_CLEAR()
{
    LCD_CMD(0);
    LCD_CMD(1);
}


//set corser position
void LCD_SET_CORSER(unsigned char r, unsigned char c)
{
    unsigned char temp, low4, high4;
    if(r == 1)
    {
        temp = 0x80 + c - 1;
        high4 =  temp >> 4;
        low4 = temp & 0x0F;
        LCD_CMD(high4);
        LCD_CMD(low4);   
        
    }
    if (r == 2)
    {
        temp = 0xC0 + c - 1;
        high4 =  temp >> 4;
        low4 = temp & 0x0F;
        LCD_CMD(high4);
        LCD_CMD(low4);
    }
}


// shift the display to LEFT
void LCD_SL()
{
    LCD_CMD(0x01);
    LCD_CMD(0x08);
}

//shift the display to RIGHT
void LCD_SR()
{
    LCD_CMD(0x01);
    LCD_CMD(0x0C);
}

