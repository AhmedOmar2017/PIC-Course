

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
    
    unsigned char I2C_read(void)
    {
        unsigned char Data;
        I2C_WAIT();
        RCEN = 1;
        I2C_WAIT();
        Data = SSPBUF;
        I2C_NACK();
        return Data;
    }
#endif
    
    
#if (SLAVE == 1)
    
    void I2C_SLAVE_INIT(void)
    {
        TRISB0= 1;
        TRISB1= 1;
        SSPADD = ADDRES;
        SSPSTAT = 0x80; // DISABLE SLEW RATE
        SSPCON1 = 0X36; // SLAVE MODE 
        SSPIF = 0;      // ENABLE INTTERUPT
        SSPIE = 1;
        PEIE = 1;
        GIE = 1;
    }
    
    
    
    void __interrupt() ISR(void)
    {
        if(SSPIF)
        {
            SKP = 0; // hold the clock stretch clock line low
            if(SSPOV || WCOL)       // Bus collision or overflow
            {
                char dummy = SSPBUF;    // read the last byte to clear the buffer
                SSPOV = 0;              // clear the overflow
                WCOL = 0;               // clear the collision 
                CKP = 1;                // release the clock line                
            }
            if(!R_nW)       // read
            {
                char dummy = SSPBUF;    // read the last byte to clear the buffer
                while(!BF);
                RX_Data = SSPBUF;       // read the receive data byte
                CKP = 1;                // release the clock line     
            }
            else if (!R_nW)
            {
                char dummy = SSPBUF;    // read the last byte to clear the buffer
                BF = 0;
                SSPBUF = dummy;         // Write your data 
                CKP = 1;                // release the clock line   
            }
            SSPIF = 0;
        }
    }
    
    
#endif    