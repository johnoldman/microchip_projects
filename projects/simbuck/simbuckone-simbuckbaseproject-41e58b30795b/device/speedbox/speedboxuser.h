/********************************************************************
 FileName:		speedboxuser.h
 Dependencies:	See INCLUDES section
 Processor:		PIC18 and PIC32 USB Microcontrollers
 Hardware:		This demo is intended to be used on Simbuck Baseboard4550
 				boards supported by the MCHPFSUSB stack.
 Complier:  	Microchip C18 (for PIC18), C32 (for PIC32)
 Company:		Deben Enterprises Ltd



 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
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
#ifndef SPEEDBOXUSER_H
#define SPEEDBOXUSER_H

/** I N C L U D E S **********************************************************/


/** D E F I N I T I O N S ****************************************************/


/** V A R I A B L E S  *******************************************************/


/** S T R U C T U R E S ******************************************************/


/** P U B L I C  P R O T O T Y P E S *****************************************/
int ProcessSpeedboxUser(void);
void InitSpeedboxInterrupts(void);

#endif //SPEEDBOXUSER_H
