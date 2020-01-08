/********************************************************************
 FileName:	CAN_ProcessMsgCAN2.h
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

********************************************************************************
 File Description:

 Change History:
  Rev   Description
  ----  ------------------------------------------------------------------------

  1.0.0 First release for Simbuck - Based from original file
                                    supplied for the LIBUSB
                                    demo in the Microchip
                                    solutions Library v2011-07-14

*******************************************************************************/

#ifndef CAN_PROCESSMSGCAN2_H
#define CAN_PROCESSMSGCAN2_H

/* I N C L U D E S **********************************************************/
#include "GenericTypeDefs.h"

/* D E F I N I T I O N S ****************************************************/



/* P R O T T Y P E S ***     ************************************************/
void process_CAN_2_msg(void);
void process_CAN_2_Message(WORD);


#endif // CAN_PROCESSMSGCAN2_H
