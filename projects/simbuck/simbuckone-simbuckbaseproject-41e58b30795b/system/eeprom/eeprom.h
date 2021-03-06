/********************************************************************
 FileName:	eeprom.h
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

#ifndef EEPROM_H
#define EEPROM_H

/* I N C L U D E S **********************************************************/


/* E E P R O M  M A P ******************************************************/
#define BOARDTYPE	0xFE			///< Hex value defining board
#define BOOTCLEAR	0xFF                    ///< Value to prevent 'soft' BOOT
#define BOOTVALUE	0xA5			///< Value to request BOOT mode
#define BOOTADDR	0xFF			///< BOOT address
#define SW_RESET        0xFE                    ///< RESET counter
/* P U B L I C  P R O T O T Y P E S ******************************************/
void WriteToEEPROM(char data, char address);
char ReadFromEEPROM(char address);

#endif // EEPROM_H
