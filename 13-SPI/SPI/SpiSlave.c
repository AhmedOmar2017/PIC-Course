void SPI_SLAVE_INIT()
{
    // set SPI mode to SLAVE + SS enable
    SSPM0 = 0;
    SSPM1 = 0;
    SSPM2 = 1;
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
    TRISCS3 = 1;    // SCK INPUT
    PCFG3 = 0;      // SET SS TO BE DIGITAL
    PCFG2 = 1;
    PCFG1 = 0;
    PCFG0 = 0;
    TRISA5 = 1; // SS  INPUT 
    /*-----------------------------------------------------
     * If the interrupt are needed uncomment the line below
     *-----------------------------------------------------*/
     // SSPIE = 1;
     // PEIE  = 1;
     // GIE   = 1;
     /*--------------------End of SPI interrupt---------------*/
}


uint8_t SPI_READ();
{
    uint8_t DATA;

    // CHECK IF ANY DATA are sent
    if (BF)
    {
        DATA =SSBUF; // READ THE BUFFER
        BF = 0;      // cLear  the buffer indicator bit
        SSPIF = 0;   // clear the interrupt flag
        SSPOV = 0;  // CLEAR THE OVER FLOW INDECATOR BIT 
        return DATA;
    }
}

void __interrupt ISR ()
{
    if(SSPIF)
    {
         DATA =SSBUF; // READ THE BUFFER
         SSPIF = 0;   // clear the interrupt flag
    }
}
