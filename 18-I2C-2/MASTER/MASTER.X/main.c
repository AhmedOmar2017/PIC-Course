

#include <xc.h>
#include "I2C.h"
void main(void) {
    
    TRISD = 0x00;
    PORTD = 0x00;
    I2C_MASTER_INIT();
    
    
    while(1)
    {
        I2C_start();
        I2C_WRITE(0x41);    // I2C slave address 0X40 + 1(read)
        PORTD = I2C_read();
        I2C_stop();
        __delay_ms(100);
    }
    return;
}
