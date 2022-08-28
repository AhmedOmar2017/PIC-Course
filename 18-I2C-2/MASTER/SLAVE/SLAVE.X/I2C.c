

#include "I2C.h"


void I2C_WAIT(void)
{
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}


#if(MASTER == 1)
    void I2C_MASTER_INIT (void)
    {
        SSPCON = 0x28;
        SSPCON2 = 0x00;
        SSPSTAT = 0x00;
        SSPADD = ((_XTAL_FREQ/4) / I2C_BAUD_RATE) - 1;
        TRISC3 = 1;
        TRISC4 = 1;
    }
    
    void I2C_start(void)
    {
        I2C_WAIT();
        SEN = 1;
    }
    
    void I2C_stop(void)
    {
        I2C_WAIT();
        PEN = 1;
    }

    void I2C_RESTART(void)
    {
        I2C_WAIT();
        RSEN = 1;
    }
    
    void I2C_ACK(void)
    {
        I2C_WAIT();
        ACKDT = 0;
        ACKEN = 1;
    }
    
    void I2C_NACK(void)
    {
        I2C_WAIT();
        ACKDT = 1;
        ACKEN = 1;
    }
    
    unsigned char I2C_WRITE(unsigned char Data)
    {
        I2C_WAIT();
        SSPBUF = Data;
        I2C_WAIT();
        return ACKSTAT;
    }
    
    unsigned char I2C_READ_BYTE (void)
    {
        RCEN = 1;
        while(!SSPIF);
        SSPIF =0;
        return SSPBUF;
    }
#endif
    
    
#if (SLAVE == 1)
    
    void I2C_SLAVE_INIT(unsigned char ADDRES)
    {
        SSPADD = ADDRES;
        SSPSTAT = 0x80; // DISABLE SLEW RATE
        SSPCON = 0X36; // SLAVE MODE 
        SSPCON2 = 0x01; 
        TRISC3= 1;
        TRISC4= 1;
        GIE = 1;
        PEIE = 1;
        SSPIF = 0;      // ENABLE INTTERUPT
        SSPIE = 1;        
    }
    
    
    
    void __interrupt() ISR(void)
    {
        if(SSPIF)
        {
            if(R_nW && !D_nA) // slave write 
            {
                char dammy = SSPBUF;     // dummy read
                SSPBUF = PORTB;
                CKP = 1;    //release the scl clock line 
                while(!BF);           
            }
            CKP = 0;
            SSPIF = 0;
        }
    }
    
    
#endif    