/********************************************************************
 FileName:	selftest.c
 Dependencies:	See INCLUDES section
 Processor:	PIC18 and PIC32 USB Microcontrollers
 Hardware:      Simbuck Baseboards and PIC32 USB Starter kit
 Complier:  	Microchip C18 (for PIC18), XC32 (for PIC32)
 Company:	Deben Enterprises Limited


 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
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

/* INCLUDES ******************************************************************/
#include <p18cxxx.h>
#include "simbuck_cfg.h"
#include "selftest.h"

/* C O M M O N  V A R I A B L E S *****************************************************/
#pragma udata
MCU_REGS MCU_regs;         ///< structure for user configuration



// update the data for the basic testing

    /* Port registers need fast update to track states

     PORTE 0xF84
     PORTD 0xF83
     PORTC 0xF82
     PORTB 0xF81
     PORTA 0xF80

     LATE 0xF8D
     LATD 0xF8C
     LATC 0xF8B
     LATB 0xF8A
     LATA 0xF89

     // slow update: once set shouldn't really change
     TRISE 0xF96
     TRISD 0xF95
     TRISC 0xF94
     TRISB 0xF93
     TRISA 0xF92

     INTCON
     INTCON2
     INTCON3

     PIE1
     PIE2
     PIR1
     PIR2
     IPR1
     IPR2

     */


// initialise the host application data structure
void InitHostAppStruct(void)
{
     MCU_regs._PORTE=PORTE;
     MCU_regs._PORTD=PORTD;
     MCU_regs._PORTB=PORTB;
     MCU_regs._PORTA=PORTA;
     MCU_regs._TRISE=TRISE;
     MCU_regs._TRISD=TRISD;
     MCU_regs._TRISC=TRISC;
     MCU_regs._TRISB=TRISB;
     MCU_regs._TRISA=TRISA;
     MCU_regs._LATE=LATE;
     MCU_regs._LATD=LATD;
     MCU_regs._LATB=LATB;
     MCU_regs._LATA=LATA;
     MCU_regs._INTCON=INTCON;
     MCU_regs._INTCON2=INTCON2;
     MCU_regs._INTCON3=INTCON3;
     MCU_regs._PIE1=PIE1;
     MCU_regs._PIE2=PIE2;
     MCU_regs._PIR1=PIR1;
     MCU_regs._PIR2=PIR2;
     MCU_regs._IPR1=IPR1;
     MCU_regs._IPR2=PR2;
     MCU_regs._RCON=RCON;

}

// update the host application data structure
void slowUpdate()
{
     MCU_regs._TRISE=TRISE;
     MCU_regs._TRISD=TRISD;
     MCU_regs._TRISC=TRISC;
     MCU_regs._TRISB=TRISB;
     MCU_regs._TRISA=TRISA;
     MCU_regs._PIE1=PIE1;
     MCU_regs._PIE2=PIE2;
     MCU_regs._PIR1=PIR1;
     MCU_regs._PIR2=PIR2;
     MCU_regs._IPR1=IPR1;
     MCU_regs._IPR2=PR2;
     MCU_regs._RCON=RCON;

     MCU_regs._INTCON=INTCON;
     MCU_regs._INTCON2=INTCON2;
     MCU_regs._INTCON3=INTCON3;
}

// update the host application data structure
void fastUpdate()
{
     MCU_regs._PORTE=PORTE;
     MCU_regs._PORTD=PORTD;
     MCU_regs._PORTB=PORTB;
     MCU_regs._PORTA=PORTA;
     MCU_regs._LATE=LATE;
     MCU_regs._LATD=LATD;
     MCU_regs._LATC=LATC;
     MCU_regs._LATB=LATB;
     MCU_regs._LATA=LATA;


}