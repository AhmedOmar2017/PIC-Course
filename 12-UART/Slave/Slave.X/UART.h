

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include "config.h"

#define _XTAL_FREQ 4000000


/*============================================
 *          Prototype function
 =============================================*/

// for master
void Trans_Fubction(uint8_t);

// for slave
uint8_t Receive_fuction(void);


 

#endif	/* XC_HEADER_TEMPLATE_H */

