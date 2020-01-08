/********************************************************************
 FileName:	CAN2515utils.h
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

#ifndef CAN2515UTILS_H
#define CAN2515UTILS_H

/* I N C L U D E S **********************************************************/
#include "GenericTypeDefs.h"


/* D E F I N I T I O N S ****************************************************/


/* S T R U C T U R E S ******************************************************/


/* P R O T O T Y P E S ******************************************************/
void decodeIdentifier(unsigned long, unsigned char);
unsigned long encodeIdentifier(unsigned char, unsigned long, unsigned char);
unsigned long encodeRespondToID(unsigned long, unsigned char);

void setMsgTarget(unsigned char, unsigned long, unsigned char);

void CAN_waitForDiagResponse(void);
void CAN_RecvDiagResponse(void);

unsigned char CAN2515_getmode(void);
void CAN2515_setmode(unsigned char);


#endif // CAN2515UTILS

