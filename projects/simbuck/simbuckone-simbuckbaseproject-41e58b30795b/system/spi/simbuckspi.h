/********************************************************************
 FileName:	simbuckspi.h
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
********************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  -----------------------------------------
  1.0  First release
  
********************************************************************/

#ifndef SIMBUCKSPI_H
#define SIMBUCKSPI_H

/* I N C L U D E S **********************************************************/

/* D E F I N E S **************************************************/

/* P U B L I C  P R O T O T Y P E S *******************************/
void InitSPI(void);
unsigned char WriteSPI(unsigned char);
unsigned char ReadSPI(unsigned char);


#endif // SIMBUCKSPI_H
