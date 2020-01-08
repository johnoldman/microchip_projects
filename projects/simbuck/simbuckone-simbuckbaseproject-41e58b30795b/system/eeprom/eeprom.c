/********************************************************************
 FileName:	eeprom.c
 Dependencies:	See INCLUDES section
 Processor:	PIC18 and PIC32 USB Microcontrollers
 Hardware:      Simbuck Baseboards and PIC32 USB Starter kit
 Complier:  	Microchip C18 (for PIC18), C32 (for PIC32)
 Company:	Deben Enterprises Limited


 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  ------------------------------------------------------------------------

  1.0.0 First release for Simbuck - Based from original file
                                    supplied for the LIBUSB
                                    demo in the Microchip
                                    solutions Library v2011-07-14
 
********************************************************************/

/* I N C L U D E S **********************************************************/
#include "simbuck_cfg.h"
#include "HardwareProfile.h"
#include "eeprom.h"

#if defined(SIMBUCK_BASEBOARD_4550)
 #include <p18cxxx.h>
#endif

#if defined(SIMBUCK_BASEBOARD_4685)
 #include <p18cxxx.h>
#endif

/* V A R I A B L E S ********************************************************/
#pragma udata

/* P R O T T Y P E S ********************************************************/


/* D E C L A R A T I O N S **************************************************/
#pragma code


/**
 * Write a value to EEPROM memory
 *
 * PreCondition:    None
 *
 * Input:           char data - the data byte to write to EEPROM
 *		    char address - the EEPROM byte position the data
 *				   is to be written to 
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a generic method to write a 
 *		    single byte of data to the EEPROM.
 *                  
 * Note:            None
 */
void WriteToEEPROM(char data, char address)
{

  INTCONbits.GIE = 0;		// Diable interrupts
  PIR2bits.EEIF = 0;	   		 // Clear 'written' flag

  EECON1bits.CFGS = 0;
  EECON1bits.EEPGD = 0;	// Programme EEPROM

  EECON1bits.WREN = 1;		// Write enabled

  EEADR = address;			// set address to write to
  EEDATA= data;			// set data to write

  EECON2 = 0x55;			// Required
  EECON2 = 0xAA;			// Required

  EECON1bits.WR = 1;		// Start the write

  while(!PIR2bits.EEIF)     	// WAIT!

 EECON1bits.WREN = 0;		// disable write
 INTCONbits.GIE = 1;		// Enable interrupts

}



/**
 * Write a value to EEPROM memory
 *
 * PreCondition:    None
 *
 * Input:           char address - the EEPROM byte position the data
 *				   is to be read from 
 *
 * Output:          The data byte at the selceted location
 *
 * Side Effects:    None
 *
 * Overview:        This function is a generic method to read a 
 *		    single byte of data from the EEPROM.
 *                  
 * Note:            None
 */
char ReadFromEEPROM(char address)
{
  EEADR = address;			// set address to read from
  EECON1bits.EEPGD = 0;	// Programme EEPROM
  EECON1bits.CFGS = 0;		// Access EEPROM
  EECON1bits.RD = 1;		// Start the read

  return EEDATA;
}



/* EOF eeprom.c ***************************************************************/


