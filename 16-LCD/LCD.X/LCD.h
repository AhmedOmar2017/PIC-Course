#include <xc.h>

#define _XTAL_FREQ 4000000

#define LCD_EN_DELAY 500
#define LCD_DATA_PORT_D TRISB
#define LCD_RS_D TRISB5
#define LCD_EN_D TRISB4
#define RS RB5
#define EN RB4
#define D4 RB0
#define D5 RB1
#define D6 RB2
#define D7 RB3


void LCD_INIT();   // Initialize the Lcd 4-bit interface
void LCD_CLEAR();  // clear lcd
void LCD_SL();     // shift the display to LEFT
void LCD_SR();     // shift the display to RIGHT


void LCD_CMD(unsigned char);    // send command to LCD
void LCD_DATA(unsigned char);    // send 4-BIT command to LCD
void LCD_SET_CORSER(unsigned char, unsigned char);  //set corser position
void LCD_WRITE_CHAR(char);          // write character to LCD
void LCD_WRITE_STRING(char*);       // write string to LCD
