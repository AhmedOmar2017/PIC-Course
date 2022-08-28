#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#define I2C_BAUD_RATE 100000




#if (MASTER == 1)

    void I2C_WAIT(void);
    void I2C_MASTER_INIT(void);
    void I2C_start(void);
    void I2C_stop(void);
    void I2C_RESTART(void);
    void I2C_ACK(void);
    void I2C_NACK(void);
    unsigned char I2C_WRITE(unsigned char);
    unsigned char I2C_read(void);
#endif

#if (SLAVE == 1)
    void I2C_SLAVE_INIT(void);
#endif


