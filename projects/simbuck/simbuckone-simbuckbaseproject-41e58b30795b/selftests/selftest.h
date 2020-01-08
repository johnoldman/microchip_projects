/********************************************************************
 FileName:	selftest4550.h
 Dependencies:	See INCLUDES section
 Processor:	PIC18 and PIC32 USB Microcontrollers
 Hardware:      Simbuck Baseboards and PIC32 USB Starter kit
 Complier:  	Microchip C18 (for PIC18), C32 (for PIC32)
 Company:	Deben Enterprises Limited


 THIS SOFTWARE IS PROVIDED IN AN ?AS IS? CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  1.0  First release

********************************************************************/
#ifndef SELFTEST_H
#define SELFTEST_H

/* S T R U C T U R E S ******************************************************/

/**
 * Structure to maintain a set of Register values for transfer via USB
*/

typedef struct MCU_REGS
{
     unsigned char _PORTE;
     unsigned char _PORTD;
     unsigned char _PORTC;
     unsigned char _PORTB;
     unsigned char _PORTA;
     unsigned char _TRISE;
     unsigned char _TRISD;
     unsigned char _TRISC;
     unsigned char _TRISB;
     unsigned char _TRISA;
     unsigned char _LATE;
     unsigned char _LATD;
     unsigned char _LATC;
     unsigned char _LATB;
     unsigned char _LATA;
     unsigned char _INTCON;
     unsigned char _INTCON2;
     unsigned char _INTCON3;
     unsigned char _PIE1;
     unsigned char _PIE2;
     unsigned char _PIR1;
     unsigned char _PIR2;
     unsigned char _IPR1;
     unsigned char _IPR2;
     unsigned char _RCON;

    } MCU_REGS;



/* P U B L I C  P R O T O T Y P E S *****************************************/
 void InitHostAppStruct(void);
 void slowUpdate(void);
 void fastUpdate(void);


#endif //SELFTEST_H

